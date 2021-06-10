#include <iostream>
#include <thread>
#include <fstream>
#include <cstdio>
#include <string>
#include <condition_variable>
#include <algorithm>

#include "arrus/core/api/arrus.h"

/**
 * A simple custom logger which just prints a given message to stderr.
 */
class MyCustomLogger : public ::arrus::Logger {
public:
    explicit MyCustomLogger(arrus::LogSeverity loggingLevel)
            : loggingLevel(loggingLevel) {}

    /**
     * Prints a message with given severity to stderr.
     * If the selected severity is, nothing is printed on console.
     *
     * @param severity message severity
     * @param msg message to print
     */
    void
    log(const arrus::LogSeverity severity, const std::string &msg) override {
        if(severity >= loggingLevel) {
            std::cerr << "[" << severityToString(severity) << "]: " << msg << std::endl;
        }
    }

    void
    setAttribute(const std::string &key, const std::string &value) override
    {}
private:

    std::string severityToString(const arrus::LogSeverity severity) {
        switch(severity) {
            case arrus::LogSeverity::TRACE: return "trace";
            case arrus::LogSeverity::DEBUG: return "debug";
            case arrus::LogSeverity::INFO: return "info";
            case arrus::LogSeverity::WARNING: return "warning";
            case arrus::LogSeverity::ERROR: return "error";
            case arrus::LogSeverity::FATAL: return "fatal";
            default: return "unknown";
        }
    }

    arrus::LogSeverity loggingLevel;
};

/**
 * A custom LoggerFactory.
 * The instance of this class is by ARRUS to create arrus::Logger instances.
 */
class MyCustomLoggerFactory: public ::arrus::LoggerFactory {
public:
    explicit MyCustomLoggerFactory(arrus::LogSeverity severityLevel)
            : severityLevel(severityLevel) {}

    /**
     * Returns a new Logger instance.
     */
    arrus::Logger::Handle getLogger() override {
        return std::make_unique<MyCustomLogger>(severityLevel);
    }

    arrus::Logger::Handle getLogger(
            const std::vector<arrus::Logger::Attribute> &attributes) override {
        return getLogger();
    }
private:
    ::arrus::LogSeverity severityLevel;
};


int main() noexcept {
    using namespace ::arrus::session;
    using namespace ::arrus::devices;
    using namespace ::arrus::ops::us4r;
    using namespace ::arrus::framework;
    try {
        // TODO set path to us4r-lite configuration file
        // TODO set appropriate aperture size

        ::arrus::setLoggerFactory(std::make_shared<MyCustomLoggerFactory>(::arrus::LogSeverity::TRACE));
        auto settings = ::arrus::io::readSessionSettings("C:/Users/Public/us4r.prototxt");
        auto session = ::arrus::session::createSession(settings);
        auto us4r = (::arrus::devices::Us4R *) session->getDevice("/Us4R:0");
        auto probe = us4r->getProbe(0);

        unsigned nElements = probe->getModel().getNumberOfElements().product();
        std::cout << "Probe with " << nElements << " elements." << std::endl;

		constexpr int APERTURE_SIZE = 3;

		// Rx aperture origin = 0, size = 128.
        std::vector<bool> rxAperture(nElements, false);
		for(int i = 0; i < APERTURE_SIZE; ++i) {
			rxAperture[i] = true;
		}
		// NOTE: the below vector should have size == probe number of elements.
		// This probably will be modified in the future 
		// (delays only for active tx elements will be needed).
        std::vector<float> delays(nElements, 0.0f);

        Pulse pulse(6e6, 2, false);
        ::std::pair<::arrus::uint32, arrus::uint32> sampleRange{0, 2048};

        std::vector<TxRx> txrxs;

		// Transmit using elements 0-127
        for(int i = 0; i < APERTURE_SIZE; ++i) {
            arrus::BitMask txAperture(nElements, false);
			// Transmit pulse using single element.
			txAperture[i] = true;
            txrxs.emplace_back(Tx(txAperture, delays, pulse),
                               Rx(rxAperture, sampleRange),
                               100e-6f);
        }

        TxRxSequence seq(txrxs, {}, 500e-3f);
        DataBufferSpec outputBuffer{DataBufferSpec::Type::FIFO, 4};
        Scheme scheme(seq, 2, outputBuffer, Scheme::WorkMode::HOST);

        auto result = session->upload(scheme);
		us4r->setVoltage(5);

        std::condition_variable cv;
        using namespace std::chrono_literals;

        OnNewDataCallback callback = [&, i = 0](const BufferElement::SharedHandle &ptr) mutable {
            try {
                std::cout << "Iteration: " << i << ", data: " << std::endl;
                std::cout << "- memory ptr: " << std::hex
                                           << ptr->getData().get<short>()
                                           << std::dec << std::endl;
                std::cout << "- size: " << ptr->getSize() << std::endl;
                std::cout << "- shape: (" << ptr->getData().getShape()[0] <<
                                     ", " << ptr->getData().getShape()[1] <<
                                     ")" << std::endl;

                // Stop the system after 10-th frame.
                if(i == 9) {
                    cv.notify_one();
                }
                ptr->release();
                ++i;
            } catch(const std::exception &e) {
                std::cout << "Exception: " << e.what() << std::endl;
                cv.notify_all();
            } catch (...) {
                std::cout << "Unrecognized exception" << std::endl;
                cv.notify_all();
            }
        };

        OnOverflowCallback overflowCallback = [&] () {
            std::cout << "Data overflow occurred!" << std::endl;
            cv.notify_one();
        };

        // Register the callback for new data in the output buffer.
        auto buffer = std::static_pointer_cast<DataBuffer>(result.getBuffer());
        buffer->registerOnNewDataCallback(callback);
        buffer->registerOnOverflowCallback(overflowCallback);

        session->startScheme();

        // Wait for callback to signal that we hit 10-th iteration.
        std::mutex mutex;
        std::unique_lock<std::mutex> lock(mutex);
        cv.wait(lock);

        // Stop the system.
        session->stopScheme();

    } catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    return 0;
}
