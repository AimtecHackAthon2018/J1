import math

class Point:
	def __init__(self,x,y):
		self.x = x
		self.y = y

	def __repr__(self):
		return '[' + str(self.x) + ':' + str(self.y) + ']'

	def getDistanceTo(self, other):
		return math.sqrt((self.x-other.x)**2+(self.y-other.y)**2)

	def getAngleTo(self, other):
		dx = other.x - self.x
		dy = other.y - self.y
		# if abs(dx) < 0.01:
		# 	return 0
		angle = math.atan2(dy,dx)*180/math.pi
		if angle < 0:
			angle += 360
			
		elif angle > 360:
			angle -= 360

		return angle

def getTimeDiff(t1,t2):
	#h_diff = abs(int(t1[11:13]) - int(t2[11:13]))
	m_diff = abs(int(t1[14:16]) - int(t2[14:16]))
	s_diff = abs(int(t1[17:19]) - int(t2[17:19]))
	ms_diff = abs(int(t1[20:]) - int(t2[20:]))
	return(ms_diff + s_diff*1000 + m_diff*1000*60)


# t1 = '2017-09-06 15:01:12.142'
# t2 = '2017-09-06 15:01:12.161'
# print getTimeDiff(t1,t2)
# p = Point(1,1)
# p2 = Point(1,1)
# print p.getDistanceTo(p2)
# print p.getAngleTo(p2)
