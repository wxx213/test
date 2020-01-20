package redistest;

import java.util.List;

import redis.clients.jedis.Jedis;
public class RedisTest {

	public static void StringTest() {
		//连接本地的 Redis 服务
		Jedis jedis = new Jedis("172.17.0.2");
		System.out.println("连接状态："+jedis.ping());
		//设置 redis 字符串数据
		jedis.set("runoobkey", "www.runoob.com");
		// 获取存储的数据并输出
		System.out.println("redis 存储的字符串为: "+ jedis.get("runoobkey"));
	}

	public static void ListTest() {
		//连接本地的 Redis 服务
		Jedis jedis = new Jedis("172.17.0.2");
		System.out.println("连接状态："+jedis.ping());
		//存储数据到列表中
		jedis.lpush("site-list", "Runoob");
		jedis.lpush("site-list", "Google");
		jedis.lpush("site-list", "Taobao");
		// 获取存储的数据并输出
		List<String> list = jedis.lrange("site-list", 0 ,2);
		for(int i=0; i<list.size(); i++) {
			System.out.println("列表项为: "+list.get(i));
		}
	}

	public static void main(String[] args) {
		// StringTest();
		// ListTest();
		RedisClusterTest.testCluster();
	}
}
