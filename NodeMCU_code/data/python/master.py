from time import sleep
import ujson
import machine

backup = {'patio': 'DESLIGADA', 'cozinha': 'DESLIGADA', 'sala': 'DESLIGADA', 'escada': 'OFF', 'escritorio': 'OFF', 'quarto': 'OFF', 'patiol': 'OFF', 'cozinhal': 'OFF', 'salal': 'OFF', 'escadal': 'OFF', 'escritoriol': 'OFF', 'quartol': 'OFF', 'gtemp': '0', 'glum': '0', 'gpres': '0'}
spatio = machine.Pin(12, machine.Pin.IN)
rpatio = machine.Pin(13, machine.Pin.OUT)

def sens(p):
    print(spatio.value())

def lerjson():
    try:
        arquivo_json = open('data.json', 'r')
        dados_json = ujson.load(arquivo_json)
        arquivo_json.close()
    except Exception as erro:
        print('Usando Backup, Oops! {}'.format(erro))
        dados_json = backup
    return dados_json

def gravarjson(vstr):
    arquivo_json = open('data.json', 'w')
    arquivo_json.write(vstr)
    arquivo_json.close()
    print('salvo...')
    return

def patio(vstr):
    dados_json = lerjson()
    dados_json['patio'] = vstr
    final_json = ujson.dumps(dados_json)
    gravarjson(final_json)
    return

def cozinha(vstr):
    dados_json = lerjson()
    dados_json['cozinha'] = vstr
    final_json = ujson.dumps(dados_json)
    gravarjson(final_json)
    return

def sala(vstr):
    dados_json = lerjson()
    dados_json['sala'] = vstr
    final_json = ujson.dumps(dados_json)
    gravarjson(final_json)
    return

def escada(vstr):
    dados_json = lerjson()
    dados_json['escada'] = vstr
    final_json = ujson.dumps(dados_json)
    gravarjson(final_json)
    return

def escritorio(vstr):
    dados_json = lerjson()
    dados_json['escritorio'] = vstr
    final_json = ujson.dumps(dados_json)
    gravarjson(final_json)
    return

def quarto(vstr):
    dados_json = lerjson()
    dados_json['quarto'] = vstr
    final_json = ujson.dumps(dados_json)
    gravarjson(final_json)
    return

def sensores():
    print('trigged func sensores')
    dados_json = lerjson()
    dados_json['patiol'] = wspatio
    final_json = ujson.dumps(dados_json)
    gravarjson(final_json)
    print('Sensores Lidos e Salvos')
    return

def wpatiol():
    dados_json = lerjson()
    inst = dados_json['patiol']
    if inst == 'ON':
        rpatio.on()
    else:
        rpatio.off()
    print('loooop')
    sleep(1)
    wpatiol()
    return

def teste(vstr):
    dados_json = lerjson()
    dados_json['patiol'] = vstr
    final_json = ujson.dumps(dados_json)
    gravarjson(final_json)
    print('done')
    return

spatio.irq(trigger=machine.Pin.IRQ_RISING | machine.Pin.IRQ_FALLING, handler=sens)
