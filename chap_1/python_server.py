# Save as daytime_server.py and run with: python3 daytime_server.py
import socket
import time

HOST = '127.0.0.1'  # localhost
PORT = 13           # daytime protocol port

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen()
    print(f"Daytime server running on {HOST}:{PORT}")
    while True:
        conn, addr = s.accept()
        with conn:
            print(f"Connected by {addr}")
            daytime_str = time.strftime('%Y-%m-%d %H:%M:%S\n', time.gmtime())
            conn.sendall(daytime_str.encode())

