import gym
import socket

HOST = '127.0.0.1'
PORT = 7794

class custom_env(gym.Env):
    def __init__(self):
        self.action_space = gym.spaces.Discrete(2)
        self.observation_space = gym.spaces.Box(-180, 180, [1])

        print(self.observation_space.high)
        print(self.observation_space.low)

        self.hasConnection = False
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

        try:
            self.socket.connect((HOST, PORT))
            print("successfully connected")
            self.hasConnection = True
        except socket.error:
            print("couldn't connect" + socket.error)

    def step(self, action):

        self.socket.send(bytes([action]))

        state = 1

        # wait till you get a response
        while(True):
            data = self.socket.recv(10)
            if not data:
                break

            state = int.from_bytes(data, byteorder='big', signed=True)

            break
    
        reward = 1 - abs(state)/20
            
        done = False
        if(abs(state) > 50):
            done = True

        info = {}
        return state, reward, done, info

    def reset(self):
        self.socket.send(bytes([10]))

        state = 1

        # wait till you get a response
        while(True):
            data = self.socket.recv(10)
            if not data:
                break

            state = int.from_bytes(data, byteorder='big', signed=True)

            break
        state = 0
        return state

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    try:
        s.connect((HOST, PORT))
        print("success")

        while(True):
            s.send(bytes([1]))

            while(True):
                data = s.recv(10)
                if not data:
                    break

                print(data)
                break

    except socket.error:
        print("couldn't connect" + socket.error)