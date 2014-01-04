#include <map>
#include <string>
#include <iostream>
#include "Md5.h"
#include "consistent.h"
#include <string.h>

struct SdbmHash
{
	size_t operator()(const char * str) const
	{
		
		size_t c;

		CMD5 md5;
		md5.GenerateMD5((unsigned char*)str, strlen(str));
		c = ((long) (md5.m_data[3] & 0xFF) << 24) 
		    | ((long) (md5.m_data[2] & 0xFF) << 16) 
		    | ((long) (md5.m_data[1] & 0xFF) << 8)
		    | (long) (md5.m_data[0] & 0xFF);  
		return c;
	}
};

class CacheServer
{
public:
	typedef std::map<std::string, std::string> StringMap;

	void Put(const std::string& key, const std::string& value)
	{
		cache_[key] = value;
	}

	std::string Get(const std::string& key) const
	{
		std::string value;
		StringMap::const_iterator it = cache_.find(key);
		if (it != cache_.end()) {
			value = it->second;
		}
		return value;
	}

	void Remove(const std::string& key)
	{
		StringMap::iterator it = cache_.find(key);
		if (it != cache_.end()) {
			cache_.erase(it);
		}
	}

private:
	StringMap cache_;
};

int test_hash()
{
	typedef std::map<std::string, CacheServer> ServerMap;
	ServerMap servers;
	typedef std::map<std::string, long> HitMap;
	HitMap 	hits;
	Consistent::HashRing<std::string, std::string, SdbmHash> ring(4, SdbmHash());

	// Create some cache servers
	servers["cache1.example.com"] = CacheServer();
	servers["cache2.example.com"] = CacheServer();
	servers["cache3.example.com"] = CacheServer();
	
	
	
	// Add their host names to the hash ring
	for (ServerMap::const_iterator it = servers.begin(); it != servers.end(); ++it) {
		std::cout << "Adding " << it->first << " with hash " << ring.AddNode(it->first) << std::endl;
	}

  int count = 100;
	for (int i = 0;  i < count; i++)
	{
		std::string host = ring.GetNode(Stringify(i));
		std::cout << "Storing " << i << " on server " << host << std::endl;
		servers[host].Put(Stringify(i), Stringify(-i));
	}
	for (int i = 0; i < count; i++)
	{
		std::string host = ring.GetNode(Stringify(i));
		hits[host]++;
		std::string value = servers[host].Get(Stringify(i));
		std::cout << "Found " << i << " on server " << host << " (" << value << ")" << std::endl;
	}
	for (ServerMap::const_iterator it = servers.begin(); it != servers.end(); ++it) {
		std::cout << "STATS " << it->first << " hit hash " << hits[it->first] << std::endl;
	}
#if 0
	/////////////////////////////////////////////////////////////////////////////////////////////
	std::cout << "Remove cache1\n" ;
	ring.RemoveNode("cache1.example.com");
	hits.clear();
	
	count = 100;
	for (int i = 0;  i < count; i++)
	{
		std::string host = ring.GetNode(Stringify(i));
		std::cout << "Storing " << i << " on server " << host << std::endl;
		servers[host].Put(Stringify(i), Stringify(-i));
	}
	for (int i = 0; i < count; i++)
	{
		std::string host = ring.GetNode(Stringify(i));
		hits[host]++;
		std::string value = servers[host].Get(Stringify(i));
		std::cout << "Found " << i << " on server " << host << " (" << value << ")" << std::endl;
	}
	for (ServerMap::const_iterator it = servers.begin(); it != servers.end(); ++it) {
		std::cout << "STATS " << it->first << " hit hash " << hits[it->first] << std::endl;
	}
#endif
	std::cout << "Add cache4\n" ;
	servers["cache4.example.com"] = CacheServer();
	ring.AddNode("cache4.example.com");
	hits.clear();
	count = 100;
	for (int i = 0;  i < count; i++)
	{
		std::string host = ring.GetNode(Stringify(i));
		std::cout << "Storing " << i << " on server " << host << std::endl;
		servers[host].Put(Stringify(i), Stringify(-i));
	}
#if 0
	for (int i = 0; i < count; i++)
	{
		std::string host = ring.GetNode(Stringify(i));
		hits[host]++;
		std::string value = servers[host].Get(Stringify(i));
		std::cout << "Found " << i << " on server " << host << " (" << value << ")" << std::endl;
	}
#endif
	for (ServerMap::const_iterator it = servers.begin(); it != servers.end(); ++it) {
		std::cout << "STATS " << it->first << " hit hash " << hits[it->first] << std::endl;
	}
	return 0;
}
