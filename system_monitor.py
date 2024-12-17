import psutil
import time
import json
import serial
import pyamdgpuinfo

SystemMonitor = serial.Serial('/dev/serial/by-id/usb-Arduino__www.arduino.cc__Arduino_Uno_12550481010611720465-if00') # This needs updated per unit

gfx_card = pyamdgpuinfo.get_gpu(0)
vram_available = gfx_card.memory_info["vram_size"]

try:

    while True:
        payload = {
            "CPU" : "",
            "MEM" : "",
            "SWP" : "",
            "GPU" : "",
            "VRAM": ""
        }

    

        payload["CPU"] = str(int(psutil.cpu_percent()))
        payload["MEM"] = str(int(psutil.virtual_memory().percent)) 
        payload["SWP"] = str(int(psutil.swap_memory().percent))
        payload["GPU"] = str(int(gfx_card.query_load() * 100 ))
        payload["VRAM"] = str(int((gfx_card.query_vram_usage()/vram_available) * 100))

        payload = json.dumps(payload) + "\n"

        SystemMonitor.write(payload.encode('ascii'))

        time.sleep(1)
except Exception:
    pass
finally:
    SystemMonitor.close()

