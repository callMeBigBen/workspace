import multiprocessing
from multiprocessing import Manager,Process,Pool
import time

MAX_WORKER_NUM = 10

def worker(k,v,single_task_result,manager):
    print 'here'
    d = {k:v}
    print d
    single_task_result.append(d)
    time.sleep(1)

def task(single_task_result,data,pool,process_list,manager):
    for key in data.keys():
        pool.apply_async(func=worker,args=(key,data[key],single_task_result,manager))
        # p.start()
        # process_list.append(p)


def main():
    print time.asctime( time.localtime(time.time()) )
    manager = Manager()
    data = manager.dict()
    data.update({1:"a",2:"b",3:"c"})
    task_num = 10
    pool = Pool(10)
    task_diff_result = manager.dict()
    process_list = []
    for i in range(0,task_num):
        single_task_result = manager.list()
        task_diff_result[i] = single_task_result
        task(single_task_result,data,pool,process_list,manager)
    # print process_list
    # for p in process_list:
    #     p.join()
    # pool.start()
    # pool.close()
    # pool.join()
    time.sleep(3)
    print task_diff_result
    print time.asctime(time.localtime(time.time()))


if __name__ == "__main__":
    main()