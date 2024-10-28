Basic and limited scanner that checks for live hosts by attempting a TCP connection to a specific port across a range of IP addresses. This will only detect hosts that respond on the target port (e.g., port 80 for HTTP), not open all ports. A more complete port scanner would require significant additional handling.
IP Range: This scans the 192.168.1.x range for simplicity, which you may need to adjust to match your network’s subnet.
Timeout: The program uses a 1-second timeout, meaning it’ll wait up to 1 second per IP to determine if the host is live.
Non-blocking Connect: The socket is set to non-blocking mode to check if the port is open without hanging indefinitely.

No Port Range: This code only checks one port (80). For multiple ports, you’d need to iterate over a port list.
Permissions: Running this requires root privileges on most systems.
Error Handling: This example includes minimal error handling.
