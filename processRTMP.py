print("in python")
import cv2
import socket
# import sys

# sys.stdout.flush()
# using flush to send data to the server immediately
# ref: https://stackoverflow.com/a/10019605

print("finish import")

serverIP = socket.gethostbyname(socket.gethostname())
print("server ip: ", serverIP)

cap = cv2.VideoCapture("rtmp://" + serverIP + ":1936/live/stream")
i = 0
while(True):
    ret, frame = cap.read()
    # print(frame)
    cv2.imshow('frame ',frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
    if i % 10 == 0:  # take 1 frame out of 10
        print("frame ", i, flush=True)
    i += 1

cap.release()
cv2.destroyAllWindows()
print("exit python")
