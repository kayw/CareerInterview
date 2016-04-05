package career_interview

// http://blog.csdn.net/zhouworld16/article/details/16882131
// http://www.makuiyu.cn/2015/01/LeetCode_14.%20Longest%20Common%20Prefix/
func LongestStringsCommonPrefixNM(strs []string) string {
	if len(strs) == 0 {
		return ""
	}
	var prefix = strs[0]
	for i := 1; i < len(strs); i++ {
		j := 0
		println("prefix:", prefix, "current match:", strs[i])
		for ; j < len(prefix) && j < len(strs[i]); j++ {
			println(prefix[j], strs[i][j])
			if prefix[j] != strs[i][j] {
				break
			}
		}
		prefix = prefix[:j]
		println("next prefix:", prefix)
	}
	return prefix
}
