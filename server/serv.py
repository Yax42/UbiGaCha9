#!/usr/bin/env python

from twisted.internet.protocol import Protocol, Factory
from twisted.internet import reactor

class Echo(Protocol):

    def __init__(self):
        self.scores =  [("aaa", 4242), ("bbb", 2121), ("ccc", 1212), ("dddd", 100), ("eeee", 42)]


    def dataReceived(self, data):
        dataList = data.split()
        if dataList[0] == "SendScore":
            self.addScore(dataList[1] , int(dataList[2]))
            self.transport.write("OK\n")
        elif dataList[0] == "GetScore":
            self.transport.write(self.formatScores())
        else:
            self.transport.write("KO\n")

    def formatScores(self):
        res = "SCORE "
        for login, score in self.scores:
            res += "{0:10s} {1:20d};".format(login, score)
        res += "\n"
        return res

    def addScore(self, login, score):
        i = 0
        for l, s in self.scores:
            if s <= score:
                print(self.scores)
                self.scores.insert(i, (login, score))
                print(self.scores)
                if (len(self.scores) > 5):
                    self.scores = self.scores[:5]
                    break
            i = i + 1

def main():
    f = Factory()
    f.protocol = Echo
    reactor.listenTCP(4242, f)
    reactor.run()

if __name__ == '__main__':
    main()
