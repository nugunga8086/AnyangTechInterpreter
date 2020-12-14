PROJECT ( "QuantumCompilerInterpreter_Project_QCI_Project" )

ADD_EXECUTABLE (
	../QCI      				# 타겟 파일
	../Source/QCI_Start.c 		# 메인 파일
	../Source/Strings.c 		# 스트링 파일
)

SET ( CMAKE_BUILD_TYPE Debug )