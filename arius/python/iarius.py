# This file was automatically generated by SWIG (http://www.swig.org).
# Version 4.0.1
#
# Do not make changes to this file unless you know what you are doing--modify
# the SWIG interface file instead.

from sys import version_info as _swig_python_version_info

if _swig_python_version_info < (2, 7, 0):
    raise RuntimeError("Python 2.7 or later required")

# Import the low-level C/C++ module
if __package__ or "." in __name__:
    from . import _iarius
else:
    import _iarius

try:
    import builtins as __builtin__
except ImportError:
    import __builtin__


def _swig_repr(self):
    try:
        strthis = "proxy of " + self.this.__repr__()
    except __builtin__.Exception:
        strthis = ""
    return "<%s.%s; %s >" % (
    self.__class__.__module__, self.__class__.__name__, strthis,)


def _swig_setattr_nondynamic_instance_variable(set):
    def set_instance_attr(self, name, value):
        if name == "thisown":
            self.this.own(value)
        elif name == "this":
            set(self, name, value)
        elif hasattr(self, name) and isinstance(getattr(type(self), name),
                                                property):
            set(self, name, value)
        else:
            raise AttributeError(
                "You cannot add instance attributes to %s" % self)

    return set_instance_attr


def _swig_setattr_nondynamic_class_variable(set):
    def set_class_attr(cls, name, value):
        if hasattr(cls, name) and not isinstance(getattr(cls, name), property):
            set(cls, name, value)
        else:
            raise AttributeError("You cannot add class attributes to %s" % cls)

    return set_class_attr


def _swig_add_metaclass(metaclass):
    """Class decorator for adding a metaclass to a SWIG wrapped class - a slimmed down version of six.add_metaclass"""

    def wrapper(cls):
        return metaclass(cls.__name__, cls.__bases__, cls.__dict__.copy())

    return wrapper


class _SwigNonDynamicMeta(type):
    """Meta class to enforce nondynamic attributes (no new attributes) for a class"""
    __setattr__ = _swig_setattr_nondynamic_class_variable(type.__setattr__)


class Arius(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v),
                       doc="The membership flag")
    __repr__ = _swig_repr

    def __init__(self, idx):
        _iarius.Arius_swiginit(self, _iarius.new_Arius(idx))

    __swig_destroy__ = _iarius.delete_Arius

    def SWTrigger(self):
        return _iarius.Arius_SWTrigger(self)

    def IsPowereddown(self):
        return _iarius.Arius_IsPowereddown(self)

    def Powerup(self):
        return _iarius.Arius_Powerup(self)

    def SyncClocks(self):
        return _iarius.Arius_SyncClocks(self)

    def Receive(self, address, length):
        return _iarius.Arius_Receive(self, address, length)

    def ScheduleReceive(self, address, length):
        return _iarius.Arius_ScheduleReceive(self, address, length)

    def IsReceived(self):
        return _iarius.Arius_IsReceived(self)

    def InitializeClocks(self):
        return _iarius.Arius_InitializeClocks(self)

    def InitializeRX(self):
        return _iarius.Arius_InitializeRX(self)

    def InitializeDDR4(self):
        return _iarius.Arius_InitializeDDR4(self)

    def TransferRXBufferToHost(self, dstAddress, length, srcAddress):
        return _iarius.Arius_TransferRXBufferToHost(self, dstAddress, length,
                                                    srcAddress)

    def TransferRXBufferToHostLocation(self, dstAddress, length, srcAddress):
        return _iarius.Arius_TransferRXBufferToHostLocation(self, dstAddress,
                                                            length, srcAddress)

    def LockDMABuffer(self, address, length):
        return _iarius.Arius_LockDMABuffer(self, address, length)

    def ReleaseDMABuffer(self, address):
        return _iarius.Arius_ReleaseDMABuffer(self, address)

    def EnableTestPatterns(self):
        return _iarius.Arius_EnableTestPatterns(self)

    def DisableTestPatterns(self):
        return _iarius.Arius_DisableTestPatterns(self)

    def SyncTestPatterns(self):
        return _iarius.Arius_SyncTestPatterns(self)

    def SetPGAGain(self, gain):
        return _iarius.Arius_SetPGAGain(self, gain)

    def SetLPFCutoff(self, cutoff):
        return _iarius.Arius_SetLPFCutoff(self, cutoff)

    def SetActiveTermination(self, endis, term):
        return _iarius.Arius_SetActiveTermination(self, endis, term)

    def SetLNAGain(self, gain):
        return _iarius.Arius_SetLNAGain(self, gain)

    def SetDTGC(self, endis, att):
        return _iarius.Arius_SetDTGC(self, endis, att)

    def SWNextTX(self):
        return _iarius.Arius_SWNextTX(self)

    def InitializeTX(self):
        return _iarius.Arius_InitializeTX(self)

    def GetID(self):
        return _iarius.Arius_GetID(self)

    def SetTxDelay(self, channel, value):
        return _iarius.Arius_SetTxDelay(self, channel, value)

    def SetTxFreqency(self, frequency):
        return _iarius.Arius_SetTxFreqency(self, frequency)

    def SetTxPeriods(self, nop):
        return _iarius.Arius_SetTxPeriods(self, nop)

    def SetRxAperture(self, origin, size):
        return _iarius.Arius_SetRxAperture(self, origin, size)

    def SetTxAperture(self, origin, size):
        return _iarius.Arius_SetTxAperture(self, origin, size)

    def SetRxTime(self, time):
        return _iarius.Arius_SetRxTime(self, time)

    def SetRxChannelMapping(self, srcChannel, dstChannel):
        return _iarius.Arius_SetRxChannelMapping(self, srcChannel, dstChannel)

    def SetTxChannelMapping(self, srcChannel, dstChannel):
        return _iarius.Arius_SetTxChannelMapping(self, srcChannel, dstChannel)

    def Write(self, address, data, length):
        return _iarius.Arius_Write(self, address, data, length)

    def Read(self, address, data, length):
        return _iarius.Arius_Read(self, address, data, length)

    def WriteAndRead(self, address, writedata, writelength, readdata,
                     readlength):
        return _iarius.Arius_WriteAndRead(self, address, writedata, writelength,
                                          readdata, readlength)

    def TGCEnable(self):
        return _iarius.Arius_TGCEnable(self)

    def TGCDisable(self):
        return _iarius.Arius_TGCDisable(self)

    def TGCSetSamples(self, samples, nSamples):
        return _iarius.Arius_TGCSetSamples(self, samples, nSamples)

    def GetNRxChannels(self):
        return _iarius.Arius_GetNRxChannels(self)

    def GetNTxChannels(self):
        return _iarius.Arius_GetNTxChannels(self)

    def GetNChannels(self):
        return _iarius.Arius_GetNChannels(self)


# Register Arius in _iarius:
_iarius.Arius_swigregister(Arius)
cvar = _iarius.cvar
ARIUS_VENDOR_ID = cvar.ARIUS_VENDOR_ID
ARIUS_DEVICE_ID = cvar.ARIUS_DEVICE_ID
PCIDMABarNumber = cvar.PCIDMABarNumber
AriusBarNumber = cvar.AriusBarNumber

