import os
import time
from http.server import BaseHTTPRequestHandler, HTTPServer
import platform
import psutil


HOST_NAME = '0.0.0.0' # !!!REMEMBER TO CHANGE THIS!!!
PORT_NUMBER = 8000




class MyHandler(BaseHTTPRequestHandler):
    def do_HEAD(s):
        s.send_response(200)
        s.send_header("Content-type", "text/html")
        s.end_headers()


    def do_GET(s):
        datahora = os.popen('date').read()
        uptime_seconds = psutil.boot_time()
        cpu = platform.processor()
        cpu_freq = psutil.cpu_freq().current
        cpu_usage = psutil.cpu_percent(interval=1)
        total_ram = psutil.virtual_memory().total / (1024 * 1024)
        used_ram = psutil.virtual_memory().used / (1024 * 1024)
        system_version = platform.release()


        process_list = psutil.process_iter(attrs=['pid', 'name'])


        process_html = "<ul>"
        for process in process_list:
            try:
                pid = process.info['pid']
                name = process.info['name']
                process_html += f"<li>PID: {pid}, Nome: {name}</li>"
            except (psutil.NoSuchProcess, psutil.AccessDenied, psutil.ZombieProcess):
                pass
            
        process_html += "</ul>"


        # HTML dinâmico
        html_response = f"""
        <html>
            <head>
                <title>Informacoes do Sistema</title>
            </head>
            <body>
                <h1>Info do Sistema</h1>
                <p>Data e Hora: {datahora}</p>
                <p>Uptime (segundos): {uptime_seconds} segundos</p>
                <p>Processador: {cpu}</p>
                <p>Velocidade do processador: {cpu_freq:.2f} MHz</p>
                <p>Capacidade ocupada do processador: {cpu_usage}%</p>
                <p>Quantidade de memoria RAM: {total_ram:.2f} MB</p>
                <p>Memoria RAM utilizada: {used_ram:.2f} MB</p>
                <p>Versao do sistema: {system_version}</p>
                <p>Processos em execuçao:</p>
                {process_html}
                <p>Voce acessou o caminho: {s.path}</p>
            </body>
        </html>
        """


        s.send_response(200)
        s.send_header("Content-type", "text/html")
        s.end_headers()
        s.wfile.write(html_response.encode())


if __name__ == '__main__':
    httpd = HTTPServer((HOST_NAME, PORT_NUMBER), MyHandler)
    print("Servidor Iniciado - %s:%s" % (HOST_NAME, PORT_NUMBER))
    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        pass
    httpd.server_close()
    print("Servidor Parado - %s:%s" % (HOST_NAME, PORT_NUMBER))
