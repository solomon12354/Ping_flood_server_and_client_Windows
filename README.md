# Ping_of_Death_server_and_client_Windows

A ping of death is a type of attack on a computer system that involves sending a malformed or otherwise malicious ping to a computer.

A correctly formed ping packet is typically 56 bytes in size, or 64 bytes when the Internet Control Message Protocol (ICMP) header is considered, and 84 bytes including Internet Protocol (IP) version 4 header. However, any IPv4 packet (including pings) may be as large as 65,535 bytes. Some computer systems were never designed to properly handle a ping packet larger than the maximum packet size because it violates the Internet Protocol.[1][2] Like other large but well-formed packets, a ping of death is fragmented into groups of 8 octets before transmission. However, when the target computer reassembles the malformed packet, a buffer overflow can occur, causing a system crash and potentially allowing the injection of malicious code.

In early implementations of TCP/IP, this bug is easy to exploit and can affect a wide variety of systems including Unix, Linux, Mac, Windows, and peripheral devices. As systems began filtering out pings of death through firewalls and other detection methods, a different kind of ping attack known as ping flooding later appeared, which floods the victim with so many ping requests that normal traffic fails to reach the system (a basic denial-of-service attack).

And this source uses the ping on Windows to process the attack on a computer. But we use ICMP packet to ping the computer you want to attack.

# Steps:

1.Download the visual studio 2019

2.Create a project the it has two files

3.Compile it.

If you can not use the function, you have to follow this steps:

1.Open your project

2.Choose Project -> properties -> C/C++ -> SDL check -> No


# Reference:

[1] Ping of Death wikipedia (May 2022):https://en.wikipedia.org/wiki/Ping_of_death

[2] C/C++ socket程式設計教程之三：Windows下的socket程式 (Febuary 2019):https://www.796t.com/content/1549136912.html

[3] How can i create a multithread in C for windows? (December 2011):https://stackoverflow.com/questions/8446757/how-can-i-create-a-multithread-in-c-for-windows

# Warning:
This project is used for the Academic Research only. Do not use it for attacking other computers. I am not responsible for all the illegal actions of other people who use this project. Thank you.


