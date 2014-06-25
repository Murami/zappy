#include		"AThread.hh"

static void		*start_thread(void *data)
{
  AThread*		thread;

  thread = reinterpret_cast<AThread*>(data);
  return (thread);
}

AThread::AThread()
{
}

void			AThread::start()
{
  if (pthread_create(&_thread, NULL, start_thread, this) == -1)
    throw (std::runtime_error("Error creating thread"));
  run();
}

void			AThread::stop()
{
  pthread_cancel(_thread);
}

AThread::~AThread()
{
}
