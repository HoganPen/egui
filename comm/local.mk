pkglib_LTLIBRARIES += library/libcomm.la
library_libcomm_la_SOURCES = %D%/egui_uds.c \
					 %D%/event_listener.c \
					 %D%/request.c \
					 %D%/message.c \
					 %D%/respond.c \
					 %D%/egui_comm.c \
					 %D%/incode.c \
					 %D%/decode.c
library_libcomm_la_LIBADD = library/libdata_structures.la
nobase_pkginclude_HEADERS += %D%/egui_uds.h \
							 %D%/event_listener.h \
							 %D%/egui_comm.h \
							 %D%/message.h \
							 %D%/packet.h \
							 %D%/request.h \
							 %D%/respond.h \
							 %D%/external.h \
							 %D%/comm.h \
							 %D%/incode.h \
							 %D%/decode.h
library_libcomm_la_LDFLAGS = -version-info 1:0:0

client_cflow_SRC += $(library_libcomm_la_SOURCES)

server_cflow_SRC += $(library_libcomm_la_SOURCES)
