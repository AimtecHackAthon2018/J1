#!/usr/bin/env python
import socket
import time
from utils import *
import car
import sys
from BaseHTTPServer import BaseHTTPRequestHandler, HTTPServer
import SocketServer
import time
import threading, resource

UDP_IP = "192.168.1.23"
UDP_PORT = 8888
STOP = 'a\n'
BACK = 'f\n'
LEFT_F = 'b\n'
RIGHT_F = 'd\n'
LEFT = 'h\n'
RIGHT = 'i\n'
END = 'end'

g_angle = '3'
g_position = '22'
g_acc = '2424'

# ///////////////////////
# WEB SERVERR
# ///////////////////////

class S(BaseHTTPRequestHandler):
	def _set_headers(self):
		self.send_response(200)
		self.send_header('Content-type', 'text/html')
		self.end_headers()

	def do_GET(self):
		global g_angle, g_position, g_acc
		self._set_headers()
		s = str(g_angle) + ' ' + str(g_position) + ' ' + str(g_acc)
		self.wfile.write(s)

	def do_HEAD(self):
		self._set_headers()
		
	def do_POST(self):
		# Doesn't do anything with posted data
		self._set_headers()
		self.wfile.write("<html><body><h1>POST!</h1></body></html>")
		
def run_server(server_class=HTTPServer, handler_class=S, port=80):
	server_address = ('', port)
	httpd = server_class(server_address, handler_class)
	print 'Starting httpd...'
	httpd.serve_forever()

# ///////////////////////
# END WEB SERVERR
# ///////////////////////

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
	global g_angle, g_position, g_acc
	it = 0
	action = STOP
	goal_id = 0
	goal = goals[goal_id]
	print "GOAL = " + str(goal)
	while True:
		if it%2 == 0:
			[action, g_angle, g_position, g_acc] = car.getAction(goal)
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
	resource.setrlimit(resource.RLIMIT_NOFILE, (12000,resource.RLIM_INFINITY))
	# RUN webserver for backend
	wst = threading.Thread(target=run_server)
	wst.daemon = True
	wst.start()

	# Run car algpo
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