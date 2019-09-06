
from iocbuilder import Device, AutoSubstitution, Architecture
from iocbuilder.arginfo import *

from iocbuilder.modules.ADCore import ADCore, ADBaseTemplate, includesTemplates, makeTemplateInstance
from iocbuilder.modules.asyn import AsynPort

@includesTemplates(ADBaseTemplate)

class _pcowinTemplate(AutoSubstitution):
    TemplateFile="pco.template"

class _pcoDeviceFirmwareTemplate(AutoSubstitution):
    TemplateFile="pco_device_firmware.template"

class pcowin(AsynPort):
    """Create a PCO camera detector"""
    Dependencies = (ADCore,)
    _SpecificTemplate = _pcowinTemplate
    _DeviceTemplate = _pcoDeviceFirmwareTemplate
    UniqueName = "PORT"

    def __init__(self, PORT, BUFFERS=50, MEMORY=-1, NUM_CAMERA_DEVICES=10, **args):
        self.__super.__init__(PORT)
        self.__dict__.update(locals())
        makeTemplateInstance(self._SpecificTemplate, locals(), args)

        P = self.__dict__['args']['P']
        R = self.__dict__['args']['R']
        for device_number in range(NUM_CAMERA_DEVICES):
            self._DeviceTemplate(P=P, R=R, PORT=PORT, N=device_number)

    # __init__ arguments
    ArgInfo = _SpecificTemplate.ArgInfo + makeArgInfo(__init__,
        PORT = Simple('Port name for the detector', str),
        BUFFERS = Simple('Maximum number of NDArray buffers to be created', int),
        MEMORY  = Simple('Max memory to allocate', int),
        NUM_CAMERA_DEVICES = Simple('Maximum number of camera devices to get firmware info for', int))
    LibFileList = ['pcowin']
    DbdFileList = ['pcowinSupport']
    SysLibFileList = []
    MakefileStringList = []
    epics_host_arch = Architecture()

    # For any windows architecture, install the pcocam libraries
    # and configure the required linker flags
    if epics_host_arch.find('win') >= 0:
        LibFileList += ['SC2_DLG', 'SC2_Cam','PCO_CDlg','Pco_conv' ]
        SysLibFileList += ['windowscodecs', 'Comdlg32', 'Winspool', 'Comctl32', 'nafxcw']
        DbdFileList += ['pcowinHardwareSupport']
        if epics_host_arch.find('debug') >= 0:
            MakefileStringList += ['%(ioc_name)s_LDFLAGS_WIN32 += /NOD:nafxcwd.lib /NOD:nafxcw.lib /NOD:libcmt']
        else:
            MakefileStringList += ['%(ioc_name)s_LDFLAGS_WIN32 += /NOD:nafxcwd.lib /NOD:nafxcw.lib']

    def Initialise(self):
        print '# pcoConfig(portName, buffers, memory, numCameraDevices)'
        print 'pcoConfig("%(PORT)s", %(BUFFERS)d, %(MEMORY)d, %(NUM_CAMERA_DEVICES)d)' % self.__dict__
        if self.epics_host_arch.find('win') >= 0:
            print '# pcoApiConfig(portName)'
            print 'pcoApiConfig("%(PORT)s")' % self.__dict__
        else:
            print '# simulationApiConfig(portName)'
            print 'simulationApiConfig("%(PORT)s")' % self.__dict__

class _pcowinGangServerTemplate(AutoSubstitution):
    TemplateFile = "pco_gangserver.template"

class pcowinGangServer(Device):
    _SpecificTemplate = _pcowinGangServerTemplate
    AutoInstantiate = True

    def __init__(self, LISTENINGTCPPORT, PORT, **args):
        self.__super.__init__()
        self.__dict__.update(locals())
        makeTemplateInstance(self._SpecificTemplate, locals(), args)

    ArgInfo = _SpecificTemplate.ArgInfo + makeArgInfo(
        __init__,
        PORT = Ident('The asyn port name of the detector driver', pcowin),
        LISTENINGTCPPORT = Simple('A TCP port number for the server to listen on', int))

    def Initialise(self):
        print '# gangServerConfig(portName, listeningTcpPort)'
        print 'gangServerConfig("%(PORT)s", %(LISTENINGTCPPORT)d)' % self.__dict__

class _pcowinGangClientTemplate(AutoSubstitution):
    TemplateFile = "pco_gangconnection.template"

class pcowinGangClient(Device):
    _SpecificTemplate = _pcowinGangClientTemplate
    AutoInstantiate = True

    def __init__(self, SERVERIP, SERVERTCPPORT, PORT, **args):
        self.__super.__init__()
        self.__dict__.update(locals())
        makeTemplateInstance(self._SpecificTemplate, locals(), args)

    ArgInfo = _SpecificTemplate.ArgInfo + makeArgInfo(
        __init__,
        PORT = Ident('The asyn port name of the detector driver', pcowin),
        SERVERIP = Simple('The IP address of the gang server', str),
        SERVERTCPPORT = Simple('A TCP port number of the gang server', int))

    def Initialise(self):
        print '# gangConnectionConfig(portName, serverIp, serverTcpPort)'
        print 'gangConnectionConfig("%(PORT)s", "%(SERVERIP)s", %(SERVERTCPPORT)d)' % self.__dict__

