
#2012/7/1  yjhjstz@163.com

include ./config-x86

LIB_OBJS =	Src/File.o  \
	Src/Time.o	\
	Src/utils.o	\
	Src/unknown.o	\
	Src/Crc.o	\
	Src/Md5.o \
	Src/version.o \
   	Src/PrintLog.o \
	Src/ThreadPool.o\
	Src/hash.o \
	Src/random.o \
	Src/pool_allocator.o \
	Src/buffer.o \
	Src/bloom.o \
	Src/btree.o \
	Src/net/eventloop.o \
	Src/net/listen.o \
	Src/net/iocomponent.o \
	Src/net/session.o \
	Src/net/sock.o \
	Src/net/sockevent.o \
	Src/net/tcpcomponent.o \
	Src/net/tcpclient.o

LIB_TARGET = $(LIBDIR)/libthink.a

TEST_OBJS = Test/Test.o \
	Test/gtest-all.o \
	Test/TestComponent.o \
	Test/hashring.o \
	Test/test_bloom.o \
	Test/test_btree.o 

					
TEST_TARGET = $(BINDIR)/think

TARGET	= $(LIB_TARGET) $(TEST_TARGET)

all: $(TARGET)

$(LIB_TARGET): $(LIB_OBJS)
	$(RM) $@;
	$(AR) $(AFLAGS) $@ $^

$(TEST_TARGET):  $(EXTLIBS) $(TEST_OBJS) $(LIB_TARGET)
	$(CPP) -o $@ $^ $(LDFLAGS)
	chmod a+x  $@

.c.o:
	$(CC) -c $(CFLAGS) $^ -o $@

.cpp.o:
	$(CPP) -c $(CFLAGS) $^ -o $@

clean:
	$(RM) $(TARGET) $(LIB_OBJS) $(TEST_OBJS);


