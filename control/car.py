from utils import *
import threading
import websocket, json
import requests, time, math

destUri = "ws://192.168.90.54:8080";
X_API_KEY = "171555a8fe71148a165392904";
FEED_ID = "11"
 
posXIndex = 0
posYIndex = 1
accIndex = 4
gyroIndex = 5
magIndex = 6

class Car:
	def __init__(self,x,y):
		self.position = Point(x,y)
		self.STOP = 'a\n'
		self.LEFT_F = 'b\n'
		self.FORWARD = 'c\n'
		self.RIGHT_F = 'd\n'
		self.LEFT_B = 'e\n'
		self.BACK = 'f\n'
		self.RIGHT_B = 'g\n'
		self.END = 'end'
		self.eps = 6
		self.have_position = False
		self.theta_offset = 0

		self.acc_x = 0
		self.acc_y = 0

		self.message_counter = 0

		self.cal_acc_x = 0
		self.cal_acc_y = 0

		self.start_time = 0

		size = 3
		self.x_float_data = []
		self.y_float_data = []
		[self.x_float_data.append(0) for x in range(size)]
		[self.y_float_data.append(0) for y in range(size)]

		websocket.enableTrace(True)
		self.ws = websocket.WebSocketApp(destUri, on_message = self.on_message, on_error = self.on_error, on_close = self.on_close)
		self.ws.on_open = self.on_open
		wst = threading.Thread(target=self.ws.run_forever)
		wst.daemon = True
		wst.start()

	def getAction(self,goal):
		action = self.STOP
		theta_car = (-(self.get_theta() - 90))%360

		print "current theta = " + str(theta_car)
		print "Desired angle " + str(self.position.getAngleTo(goal))

		if abs(theta_car - self.position.getAngleTo(goal)) < self.eps:
			action = self.FORWARD
		else:
			mod1 = (theta_car - self.position.getAngleTo(goal))%360
			mod2 = (self.position.getAngleTo(goal) - theta_car)%360
			print "m1 : m2"
			print mod1, mod2
			if mod1 < mod2:
				action = self.RIGHT_F
			else:
				action = self.LEFT_F


		if (self.position.getDistanceTo(goal) < 0.6) or (self.position.getDistanceTo(goal) > 8.0): 
			action = self.END

		print "setting action " + str(action)
		acc = math.sqrt(self.acc_x**2+self.acc_y**2)
		return [action, theta_car, str(self.position), acc]

	def get_theta(self):
		r = requests.get('http://192.168.90.218:80')

		self.start_time = time.time()

		data = r.text.split()
		print "Read adngle " + str(data[0])
		print "Read acc_x" + str(data[1])
		print "Read acc_y" + str(data[2])

		self.acc_x = float(data[1])
		self.acc_y = float(data[2])

		self.on_data_arrived()

		return float(data[0]) - float(self.theta_offset)

	def on_data_arrived(self):
		num_cal = 2
		if self.message_counter > num_cal:
			self.calibrate()
		elif self.message_counter == num_cal:
			self.cal_acc_x /= num_cal
			self.cal_acc_y /= num_cal
		else:
			actual_time = time.time() - self.start_time

			self.x_float_data.append(self.acc_x)
			self.x_float_data.pop(0)

			self.y_float_data.append(self.acc_y)
			self.y_float_data.pop(0)


		self.message_counter+=1

	def calibrate(self):
		self.cal_acc_x += self.acc_x
		self.cal_acc_y += self.acc_y

	def set_theta_offset(self):
		self.theta_offset = float(self.get_theta())
		print "New offset = " + str(self.theta_offset)

	def on_message(self, ws, message):
		data = json.loads(message)
		self.position.x = float(data['body']['datastreams'][posXIndex]['current_value'])
		self.position.y = abs(float(data['body']['datastreams'][posYIndex]['current_value']))
		self.have_position = True
		print "Car is at position " + str(self.position)
 
	def on_error(self, ws, error):
		print error

	def on_close(self, ws):
		print "### closed ###"

	def on_open(self, ws):
		print "### opened ###"
		msg = "{\"headers\":{\"X-ApiKey\":\""+ X_API_KEY+"\"},\"method\":\"subscribe\", \"resource\":\"/feeds/" +FEED_ID + "\"}";
		print "Sending message..."
		print msg
		self.ws.send(msg)

	def getDegsToRight(self, cur, des):
		pass

