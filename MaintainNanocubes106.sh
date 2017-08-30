# Keep running nanocubes web
# wanghao09
# Usage: ./MaintainNanocubes106.sh

# ssh root@10.32.47.106  -p 17585
# Root1q2w

# crontab -e
# */1 * * * * sh /data/nanocube-3.2.1/MaintainNanocubes106.sh

######################## Set env ########################
export NANOCUBE_SRC=/data/nanocube-3.2.1;
export NANOCUBE_BIN=$NANOCUBE_SRC/bin;
export PATH=$NANOCUBE_BIN:$PATH;

######################## Start Nanocubes ########################
cd ${NANOCUBE_SRC}

# E550 201607-08
# NanocubesDB=$(curl 'http://10.32.47.106:29512/count' | cut -c 19-22)
NanocubesDB11609=$(curl 'http://10.32.47.106:11609/count' | cut -c 19-22)
# echo ${NanocubesDB11609}
if [ "${NanocubesDB11609}" != "root" ] 
then 
	# echo "NanocubesDB is not running. Starting..."
	# cat $NANOCUBE_SRC/data/rx5h.csv.dmp | /data/nanocube-3.2.1/bin/nanocube-leaf  -q 29512 -f 10000 &
	# cat $NANOCUBE_SRC/data/ip24data_6c_Aug2016.csv.dmp | /data/nanocube-3.2.1/bin/nanocube-leaf  -q 11607 -f 10000 &	
	# cat $NANOCUBE_SRC/data/ip24data_6c_201607-08.csv.dmp | nanocube-leaf  -q 11607 -f 10000 &
	cat $NANOCUBE_SRC/data/ip24data_6c_201607-08_L21.csv.dmp | nanocube-leaf  -q 11609 -f 10000 &

fi

# E50 and E550 on same image: 11610
NanocubesDB11610=$(curl 'http://10.32.47.106:11610/count' | cut -c 19-22)
if [ "${NanocubesDB11610}" != "root" ] 
then 
	cat $NANOCUBE_SRC/data/ip24_ep11_7c_201609_L21.csv.dmp | nanocube-leaf  -q 11610 -f 10000 &
fi

# performance for catbytes, chunksize: 12616 12617 12618
if [ "$(curl 'http://10.32.47.106:12616/count' | cut -c 19-22)" != "root" ] 
then 
	cat $NANOCUBE_SRC/data/ip24data_1c_20160708_5m_L25.dmp | nanocube-leaf  -q 12616 -f 10000  &
fi
if [ "$(curl 'http://10.32.47.106:12617/count' | cut -c 19-22)" != "root" ] 
then 
	cat $NANOCUBE_SRC/data/ip24data_1c_20160708_5m_L25s.dmp | nanocube-leaf  -q 12617 -f 10000  &
fi
if [ "$(curl 'http://10.32.47.106:12618/count' | cut -c 19-22)" != "root" ] 
then 
	cat $NANOCUBE_SRC/data/ip24data_1c_20160708_5m_L25_c2.dmp | nanocube-leaf  -q 12618 -f 10000  &
fi

######################## Start nc_web_viewer ########################
NanocubesPID8000=$(ps -ef|grep "python -m SimpleHTTPServer 8000"|grep -v grep|cut -c 9-15)
# echo ${NanocubesPID8000};

if [ "${NanocubesPID8000}" == "" ] 
then 
	# echo "Nanocubes SimpleHTTPServer is not running. Starting..."
	cd ${NANOCUBE_SRC}/extra/nc_web_viewer
	python -m SimpleHTTPServer 8000 &
fi

######################## Start webgui ########################
NanocubesPID8005=$(ps -ef|grep "python -m SimpleHTTPServer 8005"|grep -v grep|cut -c 9-15)
# echo ${NanocubesPID8005};

if [ "${NanocubesPID8005}" == "" ] 
then 
	# echo "Nanocubes webgui is not running. Starting..."
	cd ${NANOCUBE_SRC}/extra/webgui-dev
	python -m SimpleHTTPServer 8005 &
fi
