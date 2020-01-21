package redistest;

import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Set;

// import org.junit.Before;
// import org.junit.Test;
import redis.clients.jedis.HostAndPort;
import redis.clients.jedis.JedisCluster;
import redis.clients.jedis.Tuple;

public class RedisClusterTest {
    // static JedisCluster jedis = null;

    // @Before
    public static JedisCluster conn() {
		JedisCluster jedis = null;
        Set<HostAndPort> nodes = new HashSet<HostAndPort>();
        nodes.add(new HostAndPort("172.17.0.2", 6379));
        jedis = new JedisCluster(nodes);
		return jedis;
    }

    /**
     * 操作String
     */
    // @Test
    public static void operStr() {
		JedisCluster jedis = conn();

		System.out.println("开始测试string操作");
        // 添加一条数据
        jedis.set("username", "jonychen");
        // 获取一条数据
        String username = jedis.get("username");
        System.out.println("用户名：" + username);

        // 删除
        // jedis.del("username");
    }

    /**
     * 操作hash
     */
    // @Test
    public static void operHash() {
		JedisCluster jedis = conn();

		System.out.println("开始测试hash操作");
        // 添加一条
        jedis.hset("goodsInfo", "goodsName", "403-超级手机");
        // 获取一条
        String goodsName = jedis.hget("goodsInfo", "goodsName");
        System.out.println("商品名称" + goodsName);

        Map<String, String> hash = new HashMap<String, String>();
        hash.put("orderSn", "20171226122301");
        hash.put("orderStatus", "提交预订单");

        // 添加多条
        jedis.hmset("orderInfo", hash);
        System.out.println("---------------");
        // 获取多条
        List<String> strList = jedis.hmget("orderInfo", "orderSn", "orderStatus");
        for (String string : strList) {
            System.out.println(string);
        }
        System.out.println("---------------");
        // 获取全部

        Map<String, String> orderInfoMap = jedis.hgetAll("orderInfo");
        for (Entry<String, String> entry : orderInfoMap.entrySet()) {
            System.out.println(entry.getKey() + ":" + entry.getValue());
        }

        // 删除
        // jedis.hdel("orderInfo", "orderStatus");
    }

    /**
     * 操作list
     */
    // @Test
    public static void operList() {
		JedisCluster jedis = conn();

		System.out.println("开始测试list操作");
        // 添加
        for (int i = 0; i < 10; i++) {
            jedis.lpush("animals", "dog" + i, "cat" + i, "fish" + i);
        }

        // 获取
        String reString = jedis.rpop("animals");
        System.out.println(reString);
        // 分页查询 start：起始条数 end :结束条数
        List<String> strList = jedis.lrange("animals", 0, 9);
        for (String string : strList) {
            System.out.println(string);
        }
        System.out.println("----------------");
        // 获取总条数
        Long total = jedis.llen("animals");
        System.out.println("总条数" + total);
        // 删除
        // jedis.lrem("animals", 1, "dog0");
    }

    /**
     * 操作set
     */
    // @Test
    public static void operSet() {
		JedisCluster jedis = conn();

		System.out.println("开始测试set操作");
        // 添加
        jedis.sadd("members", "xiaoming", "xiaohua", "xiaohui", "xiaochen");
        // 获取
        Set<String> members = jedis.smembers("members");
        for (String string : members) {
            System.out.println(string);
        }
        // 删除
        jedis.srem("members", "xiaohui");
    }

    /**
     * 操作sorted set-自动排序
     */
    // @Test
    public static void operSortedSet() {
		JedisCluster jedis = conn();

		System.out.println("开始测试sorted set操作");
        Map<String, Double> scoreMembers = new HashMap<String, Double>();
        scoreMembers.put("小明", 89D);
        scoreMembers.put("xiaopeng", 93D);
        scoreMembers.put("小胡", 88D);
        // 添加
        jedis.zadd("score", scoreMembers);
        // 获取start ：起始条数 end：结束条数 按分数升序查询
        Set<String> strSet = jedis.zrange("score", 0, 1);
        for (String string : strSet) {
            System.out.println(string);
        }
        System.out.println("-------------");
        // 降序查询，并获取成员的分数
        Set<Tuple> tupleSet = jedis.zrevrangeWithScores("score", 0, 1);
        for (Tuple tuple : tupleSet) {
            // 成员
            String element = tuple.getElement();
            Double score = tuple.getScore();
            System.out.println(element + ":" + score);
        }
        System.out.println("-----------------");
        // 获取总条数
        Long total = jedis.zcard("score");
        System.out.println("总条数：" + total);
        // 删除
        jedis.zrem("score", "xiaopeng");
    }

	public static void testCluster() {
		operStr();
		operHash();
		operList();
	}
}
