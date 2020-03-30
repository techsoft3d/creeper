file_bases = \
    ExitAction \
	FileOpen \
	RenderMode \
	CameraOrientation \
	ProjectionMode \


for(file, file_bases) {
	SOURCES += ../../src/actions/$${file}.cpp
	HEADERS += ../../src/actions/$${file}.h
}

