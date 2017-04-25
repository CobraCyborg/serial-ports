#use c:\python27\python.exe
from glob import glob
import os
import os.path
import sys
import _winreg

def SerialPortEnum():
    SerialPorts = []
    #iterate through registry because WMI does not show virtual serial ports
    try:
        key = _winreg.OpenKey(_winreg.HKEY_LOCAL_MACHINE, r'HARDWARE\\DEVICEMAP\\SERIALCOMM')
    except WindowsError:
        return []

    i = 0
    while True:
        try:
            SerialPorts.append(_winreg.EnumValue(key, i)[1])
            SerialPorts.append(_winreg.EnumValue(key, i)[0])
            i = i + 1
        except WindowsError:
            break

    return SerialPorts

if __name__ == "__main__":
    for port in SerialPortEnum():
        print port