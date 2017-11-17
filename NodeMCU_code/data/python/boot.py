# This file is executed on every boot (including wake-boot from deepsleep)
#import esp
#esp.osdebug(None)
import gc
import webrepl
import network

def do_connect():
    sta_if = network.WLAN(network.STA_IF)
    if not sta_if.isconnected():
        print('connecting to network...')
        sta_if.active(True)
        sta_if.connect('VIVO-2520', 'C6620F2520')
        while not sta_if.isconnected():
            pass
    sta_if.ifconfig(('192.168.1.27', '255.255.255.0', '192.168.1.1', '8.8.8.8'))
    print('network config:', sta_if.ifconfig())

def main():
    webrepl.start()
    gc.collect()
    do_connect()

main()