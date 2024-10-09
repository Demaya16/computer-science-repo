#!/usr/bin/python

from mininet.topo import Topo
from mininet.net import Mininet
from mininet.util import dumpNodeConnections
from mininet.log import setLogLevel, info
from mininet.cli import CLI
from mininet.node import RemoteController

class FinalTopo(Topo):
    def build(self):
        # Create hosts for Floor 1, Switch 1
        h101 = self.addHost('h101', mac='00:00:00:00:01:01', ip='128.114.1.101/24')
        h102 = self.addHost('h102', mac='00:00:00:00:01:02', ip='128.114.1.102/24')

        # Create hosts for Floor 1, Switch 2
        h103 = self.addHost('h103', mac='00:00:00:00:01:03', ip='128.114.1.103/24')
        h104 = self.addHost('h104', mac='00:00:00:00:01:04', ip='128.114.1.104/24')

        # Create hosts for Floor 2, Switch 1
        h201 = self.addHost('h201', mac='00:00:00:00:02:01', ip='128.114.2.201/24')
        h202 = self.addHost('h202', mac='00:00:00:00:02:02', ip='128.114.2.202/24')

        # Create hosts for Floor 2, Switch 2
        h203 = self.addHost('h203', mac='00:00:00:00:02:03', ip='128.114.2.203/24')
        h204 = self.addHost('h204', mac='00:00:00:00:02:04', ip='128.114.2.204/24')

        # Create trusted and untrusted hosts
        h_trust = self.addHost('h_trust', mac='00:00:00:00:03:01', ip='192.47.38.109/24')
        h_untrust = self.addHost('h_untrust', mac='00:00:00:00:04:01', ip='108.35.24.113/24')

        # Create LLM server
        h_server = self.addHost('h_server', mac='00:00:00:00:05:01', ip='128.114.3.178/24')

        # Create switches
        s1 = self.addSwitch('s1')  # Floor 1, Switch 1
        s2 = self.addSwitch('s2')  # Floor 1, Switch 2
        s3 = self.addSwitch('s3')  # Floor 2, Switch 1
        s4 = self.addSwitch('s4')  # Floor 2, Switch 2
        s5 = self.addSwitch('s5')  # Core switch
        s6 = self.addSwitch('s6')  # Data center switch

        # Connect hosts to switches
        self.addLink(h101, s1, port1=1, port2=1)
        self.addLink(h102, s1, port1=2, port2=2)

        self.addLink(h103, s2, port1=1, port2=1)
        self.addLink(h104, s2, port1=2, port2=2)

        self.addLink(h201, s3, port1=1, port2=1)
        self.addLink(h202, s3, port1=2, port2=2)

        self.addLink(h203, s4, port1=1, port2=1)
        self.addLink(h204, s4, port1=2, port2=2)

        self.addLink(h_server, s6, port1=1, port2=1)

        # Connect floor switches to core switch
        self.addLink(s1, s5, port1=3, port2=2)
        self.addLink(s2, s5, port1=3, port2=3)
        self.addLink(s3, s5, port1=3, port2=4)
        self.addLink(s4, s5, port1=3, port2=5)
        self.addLink(s6, s5, port1=3, port2=7)  # Connect data center switch to core switch

        # Connect trusted and untrusted hosts to core switch
        self.addLink(h_trust, s5, port1=1, port2=5)
        self.addLink(h_untrust, s5, port1=1, port2=6)

def configure():
    topo = FinalTopo()
    net = Mininet(topo=topo, controller=RemoteController)
    net.start()

    CLI(net)
    net.stop()

if __name__ == '__main__':
    setLogLevel('info')
    configure()
