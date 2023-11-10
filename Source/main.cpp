#include "widget.h"
#include <QApplication>
#include<mymainwindow.h>
#include<pthread.h>
#include<unistd.h>
#include<QMutex>
#include<QSettings>
#include<QEvent>
#include<stdio.h>

#include<iostream>
#include<thread>
#include<mutex>
#include<sys/mman.h>
#include<sys/types.h>
#include<QSystemSemaphore>
#include<QSharedMemory>
#include<semaphore.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>

sem_t *sem;
//const char sem_name[]= "/sem2";

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    if(sem != 0) //SEM_FAILED
    {
        qDebug()<<"sem_open: failed error : "<<errno;
    }
    //sem_t* sem;
    int rc;
    const char sem_name[]= "semB";

    sem = sem_open(sem_name,O_CREAT ,S_IRWXU,1);
    qDebug()<<"sem_open: : "<<sem;
    qDebug()<<"sem_open: Value : "<<errno;
    if(sem ==0) //SEM_FAILED
    {
        qDebug()<<"sem_open: failed error : "<<errno;
    }

    rc = sem_trywait(sem);
    if(rc == 0)  //if success
    {
        qDebug()<<"Obtained lock!!";

        myMainWindow w;
        w.show();
        return a.exec();

    }
    else
    {
        qDebug()<<"Instance already running !!!";
    }

    if(a.closingDown())  //a.exec()==0
    {
        //sem_post(sem);
        sem_unlink(sem_name);
    }
  }

    //sem_init(&sem,1,1);
    //sem_wait(&sem);






    /*
    QSharedMemory shmem("sm");
    shmem.attach();

    QSharedMemory shmem("sm");
    if(shmem.isAttached())
    {
    }
    else
    {
     shmem.create(1);
    }
    */

    //sem_post(&sem);
    //sem_destroy(&sem);
    //sema.release();

   /*
    QApplication a(argc, argv);


      char name[15];
      int ret;
      int ret2;

      pthread_mutex_t *mutex; //  = shmat(SHARED_MEMORY_ID, NULL,0);
      mutex = (pthread_mutex_t*) mmap(NULL,getpagesize(),PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);

      pthread_mutexattr_t attr;
      ret = pthread_mutexattr_init (&attr) ;
      ret = pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED) ;
      if(ret == 0 ){ qDebug()<<"shared successfully"<<ret; }
          else { qDebug()<<" Not shared "<<ret; }


      pthread_mutex_init(mutex, &attr);
      pthread_mutexattr_destroy(&attr);
      memset(name,0,sizeof(name));
      strcpy(name,"MUTEX1");
      int rc = pthread_mutex_setname_np(&mutex ,name);
      if(rc == 0 ){ qDebug()<<"named successfully"<<ret; }
          else { qDebug()<<" Not named "<<rc; }

      pid_t pid = fork();

      if(pid == 0)
      {
          qDebug()<<"Instance running";
          return 0;
      }

      else {
          ret2 = pthread_mutex_lock(mutex);
          if(ret2 == 0 ){ qDebug()<<"locked successfully"<<ret; }
              else { qDebug()<<" Not locked "<<ret2; }


          myMainWindow w;
          w.show();
          return a.exec();

          pthread_mutex_unlock(mutex);
          pthread_mutex_destroy(mutex);
      }
      */

      //pthread_mutex_lock(&a ->mutex);
   //QEvent event;
      //QSettings setting;
     // QMutex mutex;
     //setting.setValue("mutex_Locked",false);
      // mutex.lock();
    //qDebug()<<"setting is :"<<setting.value("mutex_Locked").toBool();
   // if(setting.value("mutex_Locked").toBool()==false)
   // {
//        if(mutex.try_lock())
//        {
           // setting.setValue("checkstate",ui->remember_username_passwd_checkBox->isChecked());
               // setting.setValue("mutex_Locked",true);
                //qDebug()<<"mutex is locked";
             //   w.show();
             //   return a.exec();
               // mutex.unlock();
               // pthread_mutex_unlock(&mutex);
               // setting.setValue("mutex_Locked",false);
//        }
//        else
//        {
//                qDebug()<<"One Instance is already running";
//        }

//    employee_info w;
//    w.show();




//      }
//      else{ qDebug()<<"One Instance is already running";}

//    if( w.event() == close)
//    {
//        qDebug()<<"setting at exit 1 is :"<<setting.value("mutex_Locked").toBool();
//        mutex.unlock();
//        setting.value("mutex_Locked").toBool()==false;
//        qDebug()<<"setting at exit 2 is :"<<setting.value("mutex_Locked").toBool();
//    }

     //   pthread_mutex_unlock(&mutex);
//}
