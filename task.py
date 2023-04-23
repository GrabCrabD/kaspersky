import socket

s = socket.socket()
s.bind(('', 9090))
s.listen(1)
print("listening")


while True:
    conn, addr = s.accept()
    print("connected...", addr)
    res = b'wow'
    conn.send(res)

    conn.close()
