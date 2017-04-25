#use c:\python27\python.exe
from glob import glob
import os
import os.path
import sys
import _winreg

def enumerate():
    ports = []

	# Iterate through registry because WMI does not show virtual serial ports

    try:
        key = _winreg.OpenKey(_winreg.HKEY_LOCAL_MACHINE, r'HARDWARE\\DEVICEMAP\\SERIALCOMM')
    except WindowsError:
        return []
    i = 0
    while True:
        try:
            ports.append(_winreg.EnumValue(key, i)[1])
            i = i + 1
        except WindowsError:
            break
    return ports

def script():
    for port in enumerate():
        print port

if __name__ == "__main__":
    script()