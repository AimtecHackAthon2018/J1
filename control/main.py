#!/usr/bin/env python
import socket
import time
from utils import *
import car
import sys

UDP_IP = "192.168.1.23"
UDP_PORT = 8888
STOP = 'a\n'
BACK = 'f\n'
LEFT_F = 'b\n'
RIGHT_F = 'd\n'
LEFT = 'h\n'
RIGHT = 'i\n'
END = 'end'

def sendMessage(message):
	sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
	sock.sendto(message, (UDP_IP, UDP_PORT))

def braking(braking_time_req):
	step = 0.05
	braking_time = 0
	while True:
		sendMessage(BACK)
		time.sleep(step)
		braking_time += step
		if braking_time >= braking_time_req:
			sendMessage(STOP)
			sys.exit()

def run(car, goals):
	it = 0
	action = STOP
	goal_id = 0
	goal = goals[goal_id]
	print "GOAL = " + str(goal)
	while True:
		if it%2 == 0:
			action = car.getAction(goal)
			sendMessage(action)

			if action == END:
				goal_id += 1
				if goal_id == len(goals):
					braking(0.3)
					sendMessage(STOP)
					break
				else:
					goal = goals[goal_id]
					print "GOAL = " + str(goal)

			time.sleep(0.2)
		else:
			if action == LEFT_F:
				sendMessage(LEFT)
			elif action == RIGHT_F:
				sendMessage(RIGHT)
			else:
				sendMessage(STOP)
			time.sleep(0.1)

		it += 1
		


if __name__ == '__main__':

	our_car = car.Car(0,0)
	while False == our_car.have_position:
		time.sleep(0.2)

	our_car.set_theta_offset()
	goals = [Point(our_car.position.x - 1.5, our_car.position.y + 1.5),
			 Point(our_car.position.x, our_car.position.y + 2.5),
			 Point(our_car.position.x + 1.5, our_car.position.y + 0.5),
			 Point(our_car.position.x, our_car.position.y)]
	print "Goals = ", goals[0], goals[1], goals[2], goals[3]
	run(our_car, goals)