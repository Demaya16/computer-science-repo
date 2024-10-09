#!/usr/bin/python
from mininet.topo import Topo
from mininet.net import Mininet
from mininet.cli import CLI
class MyTopology(Topo):
  """
  A basic topology
  """
  def __init__(self):
    Topo.__init__(self)
    # Set Up Topology Here
    switch = self.addSwitch('s1') ## Adds a Switch
    hosts = [self.addHost('h{0}'.format(i)) for i in range(1, 5)]  ## Adds 4 Hosts
    for host in hosts:
        self.addLink(host, switch) ## Add a link from each host to switch
if __name__ == '__main__':
  """
  If this script is run as an executable (by chmod +x), this is
  what it will do.
 """
  topo = MyTopology() #creates the topology
  net = Mininet(topo=topo) #Loads the topo in mininet 
  net.start() #starts mininet
#cmnds to interact with topology
  CLI(net)
  net.stop() #Stops mininet
