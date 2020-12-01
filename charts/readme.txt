ROS RVIZ 插件开发
mathgl_ws
	MathGL实现的3D插件
echart_demo_ws
	echart实现的3D插件，内部基于doogie集成cef
	src/chart3d/CMakeLists.txt中定义了cef路径：
	    set(CEF_ROOT "/home/page/third_party/cef_binary_85.3.5+gd7ff358+chromium-85.0.4183.102_linux64")
	另外，该插件需要启动外部render进程doogie
doogie-0.7.8
	render进程
	
echarts_demo
	echarts js demo