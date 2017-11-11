from time import sleep
import machine
import ujson

led = machine.Pin(13, machine.Pin.OUT)
spatio = machine.Pin(12, machine.Pin.IN)

#def a():
#    se = 'foi'
#    return se

#def b ():
#    se = a()
#    print(se)


def spa():
    if spatio.value() == 1:
        print('patiol ON')
    elif spatio.value() == 0:
        print('patiol OFF')
    else:
        print('DEU BOSTA NA CONVERSÃO DE NUMERO PARA STRING')
    return

def ler():
    arquivo_json = open('data.json', 'r')
    dados_json = ujson.load(arquivo_json)
    arquivo_json.close()
    return dados_json

def pasta():
    os.listdir()
    return os.listdir()

def esc():
    dados_json = {'patio': 'DESLIGADA', 'cozinha': 'DESLIGADA', 'sala': 'DESLIGADA', 'escada': 'OFF', 'escritorio': 'OFF', 'quarto': 'OFF', 'patiol': 'OFF', 'cozinhal': 'OFF', 'salal': 'OFF', 'escadal': 'OFF', 'escritoriol': 'OFF', 'quartol': 'OFF', 'gtemp': '0', 'glum': '0', 'gpres': '0'}
    dados_json['patio'] = "TESTE"
    final_json = ujson.dumps(dados_json)
    arquivo_json = open('data.json', 'w')
    arquivo_json.write(final_json)
    arquivo_json.close()
    print('salvo...')
    return

def blink():
    print(spatio.value())
    led.on()
    sleep(0.5)
    led.off()
    return