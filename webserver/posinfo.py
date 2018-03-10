import string

class Posinfo(object):
    yaw = 0
    pitch = 0
    roll = 0

    def __init__(self, yaw, pitch, roll):
        self.yaw = yaw
        self.pitch = pitch
        self.roll = roll

    def __repr__(self):
        return "Y:%.2f P:%.2f R:%.2f" % (self.yaw,  self.pitch, self.roll)
