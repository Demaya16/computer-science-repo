from pox.core import core
import pox.openflow.libopenflow_01 as of
from pox.lib.packet.ethernet import ethernet
from pox.lib.packet.ipv4 import ipv4
from pox.lib.packet.arp import arp

log = core.getLogger()

class SimpleRouter(object):
    def __init__(self, connection):
        self.connection = connection
        connection.addListeners(self)
        self.install_rules()

    def install_rules(self):
        # Allow ARP traffic
        arp_rule = of.ofp_flow_mod()
        arp_rule.priority = 65535
        arp_rule.match.dl_type = ethernet.ARP_TYPE
        arp_rule.actions.append(of.ofp_action_output(port=of.OFPP_FLOOD))
        self.connection.send(arp_rule)

        # Allow TCP traffic
        tcp_rule = of.ofp_flow_mod()
        tcp_rule.priority = 65534
        tcp_rule.match.dl_type = ethernet.IP_TYPE
        tcp_rule.match.nw_proto = ipv4.TCP_PROTOCOL
        tcp_rule.actions.append(of.ofp_action_output(port=of.OFPP_FLOOD))
        self.connection.send(tcp_rule)

        # Drop ICMP traffic from untrusted host
        icmp_rule_untrusted = of.ofp_flow_mod()
        icmp_rule_untrusted.priority = 65533
        icmp_rule_untrusted.match.dl_type = ethernet.IP_TYPE
        icmp_rule_untrusted.match.nw_proto = ipv4.ICMP_PROTOCOL
        icmp_rule_untrusted.match.nw_src = '108.35.24.113'
        self.connection.send(icmp_rule_untrusted)

        # Drop all other IP traffic from untrusted host to internal network
        ip_rule_untrusted = of.ofp_flow_mod()
        ip_rule_untrusted.priority = 65532
        ip_rule_untrusted.match.dl_type = ethernet.IP_TYPE
        ip_rule_untrusted.match.nw_src = '108.35.24.113'
        ip_rule_untrusted.actions = []
        self.connection.send(ip_rule_untrusted)

        # Drop all traffic from untrusted/trusted host to LLM server
        for host in ['192.47.38.109', '108.35.24.113']:
            rule = of.ofp_flow_mod()
            rule.priority = 65531
            rule.match.dl_type = ethernet.IP_TYPE
            rule.match.nw_src = host
            rule.match.nw_dst = '128.114.3.178'
            rule.actions = []
            self.connection.send(rule)

        # Drop ICMP traffic from trusted host to Floor 2 hosts
        icmp_rule_trusted = of.ofp_flow_mod()
        icmp_rule_trusted.priority = 65530
        icmp_rule_trusted.match.dl_type = ethernet.IP_TYPE
        icmp_rule_trusted.match.nw_proto = ipv4.ICMP_PROTOCOL
        icmp_rule_trusted.match.nw_src = '192.47.38.109'
        icmp_rule_trusted.match.nw_dst = '128.114.2.0/24'
        self.connection.send(icmp_rule_trusted)

        # Drop ICMP traffic between Floor 1 and Floor 2 hosts
        for src in ['128.114.1.0/24', '128.114.2.0/24']:
            for dst in ['128.114.2.0/24', '128.114.1.0/24']:
                rule = of.ofp_flow_mod()
                rule.priority = 65529
                rule.match.dl_type = ethernet.IP_TYPE
                rule.match.nw_proto = ipv4.ICMP_PROTOCOL
                rule.match.nw_src = src
                rule.match.nw_dst = dst
                rule.actions = []
                self.connection.send(rule)

    def _handle_PacketIn(self, event):
        packet = event.parsed
        if not packet.parsed:
            log.warning("Ignoring incomplete packet")
            return
        packet_in = event.ofp
        log.debug("Received packet: %s", packet)

def launch():
    def start_switch(event):
        log.info("Starting SimpleRouter for %s", event.connection)
        SimpleRouter(event.connection)
    core.openflow.addListenerByName("ConnectionUp", start_switch)
