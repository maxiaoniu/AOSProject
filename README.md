# AOSProject
Advanced Operation System Project 
This a course project of distribute system. Our goal is to design a mutex exclusive algorithm and test the algorithm in a distribute environment.

My teammates were not familiar with net development. So I developed a user-level library for them to make things easy. I encapsulated low-level socket API and offered our team a friendly interface, such as “send(source_node, target_node, command)”. I also use Linux epoll technology for fast I/O and coordinated over a large number of simultaneous connections. 
