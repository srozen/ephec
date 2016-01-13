import threading
import time
import Queue

bal = Queue.Queue (100)
test = 10
class myThread(threading.Thread):
    def __init__(self, name=None):
        threading.Thread.__init__(self, target=self.run, name=name, args=() )
        self.start()

    def run(self):
        for i in range(test):
            print self.getName(), i
            bal.put ("Msg %d from %s"%(i,self.getName()))
            time.sleep (0.2)


def main ():
    t1 = myThread("Thread(1)")
    t2 = myThread("Thread(2)")

    for i in range (test*2):
        msg = bal.get ()
        print "Reception message :", msg

if __name__=="__main__":
    main ()