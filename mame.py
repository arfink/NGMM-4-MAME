import subprocess
import serial
import re

def execute(cmd):
    popen = subprocess.Popen(cmd, stdout=subprocess.PIPE, universal_newlines=True)
    for stdout_line in iter(popen.stdout.readline, ""):
        yield stdout_line 
    popen.stdout.close()
    return_code = popen.wait()
    if return_code:
        raise subprocess.CalledProcessError(return_code, cmd)


def main():
    ser = serial.Serial('/dev/ttyACM0', 57600)

    for output in execute(["mame", "neogeo", "-cart1", "mslug", "-cart2", "pbobblen", "-cart3", "lastblad", "-cart4", "pnyaa", "-output", "console"]):

        r = re.search("digit(\d*) = (\d*)", output)
        if r and r.group(1) and r.group(2):
            print(r.group(1) + "," + r.group(2) + "\n")
            ser.write(r.group(1) + "," + r.group(2) + "\n".encode())


if __name__ == "__main__":
    main()
