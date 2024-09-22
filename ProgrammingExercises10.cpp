
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <string>
#include<numeric>
//1.
std::vector<int> GetUniqueMonsters(std::vector<int> numbers)
{
    std::vector<int> answer;
    std::map<int, int> m;
    for (auto n : numbers)
    {
        m[n] = 0;
    }

    for (auto n : numbers)
    {
        if (m[n] == 0)
        {
            m[n] = 1;
        }
        else if (m[n] == 1)
        {
            m[n] = -1;
        }
    }
    for (auto n : numbers)
    {
        if (m[n] == 1)
        {
            answer.push_back(n);
        }
    }

    if (answer.empty())
    {
        answer.push_back(-1);
    }
    else
    {
        std::sort(answer.begin(), answer.end());
    }

    return answer;
}

//2.
int GetMinBlocks(const std::vector<int>& bricks, int n, int k)
{
    int i{ 1 };
    int j{ static_cast<int>(bricks.size()) - 1 };
    if (bricks[0] == n)
    {
        i++;
    }
    if (bricks[bricks.size()-1] == n)
    {
        j--;
    }

    std::vector<int> even(k - 1, 0);
    std::vector<int> odd(k - 1, 0);
    int o{}, e{};
    for (i; i < j; i++)
    {
        if (i & 1)
        {
            if (o < k-1)
            {
                odd[o] = bricks[i];
                o++;
            }
        }
        else
        {
            if (e < k-1)
            {
                even[e] = bricks[i];
                e++;
            }
        }
        
    }
    
    int sumE{}, sumO{};
    for (auto e : even)
    {
        sumE += e;
    }
    for (auto o : odd)
    {
        sumO += o;
    }

    return std::min(sumE, sumO);
}

//3.
struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

int KthSmallestInBST(TreeNode* root, int k)
{
    std::queue<TreeNode*> q;
    q.push(root);
    std::vector<int> v;
    if (q.empty())
    {
        auto head = q.front();
        v.push_back(head->val);
        q.pop();

        if (head->left) { q.push(head->left); }
        if (head->right) { q.push(head->right); }
    }

    std::sort(v.begin(), v.end());

    return v[k];
}
//R(left, k);
// if(left != -1) return left;
// k--;
// if(k==0) return node->val;
// 
// return R(right, k);

//PreOrde
//InOrde
//PostOrder

//int KthSmallestInBST(TreeNode* root, int k)
//{
//    std::vector<int> elements;
//    std::function<void(TreeNode*)> inOrder = & {
//        if (!node) return;
//        inOrder(node->left);
//        elements.push_back(node->val);
//        inOrder(node->right);
//    };
//
//    inOrder(root);
//
//    if (k >= 1 && k <= elements.size())
//        return elements[k - 1];
//    else
//        return -1; // Handle invalid k values
//}



//4.
int Research(std::vector<std::vector<int>> fielsd, int x, int y, int farmSize)
{
    int count{};
    for (int j = y; j < y + farmSize; j++)
    {
        for (int i = x; i < x + farmSize; i++)
        {
            if (fielsd[j][i] == 2)
            {
                return -1;
            }
            else if (fielsd[j][i] == 1)
            {
                count++;
            }
        }
    }
    return count;
}
int GetMinStones(std::vector<std::vector<int>> fielsd, int farmSize)
{
    std::set<int> s;
    for (int y = 0; y < fielsd.size() - farmSize; y++)
    {
        for (int x = 0; x < fielsd[0].size() - farmSize; x++)
        {
            s.insert(Research(fielsd, x, y, farmSize));
        }
    }
    if (s.size() == 1)
    {
        if (*s.begin() == -1)
        {
            return -1;
        }
        else
        {
            return *s.begin();
        }
    }

    s.erase(-1);

    return *s.begin();
}

int GetMinStones2(std::vector<std::vector<int>>& field, int farmSize)
{
    int n = field.size();
    int m = field[0].size();
  
    //stone prefixsum
    std::vector<std::vector<int>> prefixSum(n + 1, std::vector<int>(m + 1, 0));
    
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            prefixSum[i][j] = prefixSum[i - 1][j] + prefixSum[i][j - 1] - prefixSum[i - 1][j - 1] + field[i - 1][j - 1];
        }
    }
    
    //baren prefixsum
    std::vector<std::vector<int>> prefixSum2(n + 1, std::vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            prefixSum2[i][j] = prefixSum2[i - 1][j] + prefixSum2[i][j - 1] - prefixSum2[i - 1][j - 1] + (field[i - 1][j - 1] == 2? 1:0);
        }
    }

    int minStones = std::numeric_limits<int>::max();

    // 부분 블록 순회
    for (int i = 0; i <= n - farmSize; i++)
    {
        for (int j = 0; j <= m - farmSize; j++)
        {
            int wastes = prefixSum2[i + farmSize][j + farmSize] - prefixSum2[i][j + farmSize] - prefixSum2[i + farmSize][j] + prefixSum2[i][j];
            if (wastes == 0)
            {
                int stonesInBlock = prefixSum[i + farmSize][j + farmSize] - prefixSum[i][j + farmSize] - prefixSum[i + farmSize][j] + prefixSum[i][j];
                    
                minStones = std::min(minStones, stonesInBlock);
            }
        }
    }

    return (minStones == std::numeric_limits<int>::max()) ? -1 : minStones;
}

//5.
bool CanJump(std::vector<int>& nums)
{
    std::vector<bool> v(nums.size(), false);
    v[0] = true;
    for (int i = 0; i < nums.size(); i++)
    {
        if (v[i] == true)
        {
            for (int j = i; j < i + nums[i]; j++)
            {
                if (j < nums.size())
                {
                    v[j] = true;
                }
            }
        }
    }
    return v[nums.size() - 1];
}

bool CanJump2(std::vector<int>& nums)
{
    int max_reach = 0; // 현재까지 도달할 수 있는 최대 인덱스

    for (int i = 0; i < nums.size(); i++)
    {
        if (i > max_reach)
        {
            // 현재 인덱스에 도달할 수 없음
            return false;
        }

        // Update the maximum reachable index
        max_reach = std::max(max_reach, i + nums[i]);
    }

    // If we can reach the end, return true
    return true;
}


//6.
int LengthOfReplcaementSubstring(std::string s, int k)
{
    std::unordered_map<char, int> um;
    for (auto c : s)
    {
        um[c]++;
    }
    int max{};
    int possible{ um[0] };
    for (auto e : um)
    {
        max = std::max(max, e.second);
        if (e.second >= k)
        {
            possible = std::min(possible, e.second);
        }
    }

    if (max + possible > s.size())
    {
        return max;
    }

    return max + possible;
}



//7.
struct ListNode
{
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

ListNode* Merge(ListNode* l1, ListNode* l2)
{
    ListNode* head = new ListNode(0);
    ListNode* temp = head;

    while (l1 && l2)
    {
        if (l2->val <= l1->val)
        {
            temp->next = l2;
            temp = temp->next;
            l2 = l2->next;
          }
        else
        {
            temp->next = l1;
            temp = temp->next;
            l1 = l1->next;
        }
    }

    if (l1)
    {
        temp->next = l1;
    }
    else
    {
        temp->next = l2;
    }
    temp = head;
    head = head->next;
    delete(temp);

    return head;
}

ListNode* MergeLists(std::vector<ListNode*>& lists)
{
    if (lists.size() >= 2)
    {
        ListNode* head = Merge(lists[0], lists[1]);
        for (int i = 2; i < lists.size(); i++)
        {
            head = Merge(head, lists[i]);
        }
        return head;
    }
    else if (lists.size() == 1)
    {
        return lists[0];
    }
    else
    {
        return nullptr;
    }
}

//8.
int MaxStudent(std::vector<std::vector<int>>& officce, int k, int i, int j)
{
    int count{};
    for (int y = i; y < i + k; y++)
    {
        for (int x = j; x < j + k; x++)
        {
            if (officce[y][x] == 1)
            {
                count++;
            }
        }
    }
    return count;
}

int MaxWarm(std::vector<std::vector<int>>& officce, int k)
{
    int max{};
    for (int i = 0; i < officce.size()-k; i++)
    {
        for (int j = 0; j < officce[0].size()-k; j++)
        {
            max = std::max(max, MaxStudent(officce, k, i, j));
        }
    }
    return max;
}

//9.
int MaxProductOfSubArray(std::vector<int>& nums)
{
    int sum{1}, max{0};
    for (int i = 0; i < nums.size(); i++)
    {
        sum = 1;
        for (int j = i; j < nums.size(); j++)
        {
            sum *= nums[j];
            max = std::max(max, sum);
        }
    }

    return max;
}

int MaxProductOfSubArray2(std::vector<int>& nums)
{
    int max = nums[0];
    int min = nums[0];
    int answer = nums[0];

    for (int i = 1; i < nums.size(); i++)
    {
        int temp = max;
        max = std::max({ nums[i], nums[i] * max, nums[i] * min });
        min = std::min({ nums[i], nums[i] * temp, nums[i] * min });

        answer = std::max(answer, max);
    }

    return answer;
}


//10.
bool Palindrome(std::string s, int l, int r)
{
    while (l < r)
    {
        if (s[l] != s[r])
        {
            return false;
        }
        l++;
        r--;
    }
    return true;
}
std::string LongetPalindrome(std::string s)
{
    std::string answer = "";
    int maxLen{ 1 };
    for (int i = 0; i < s.length(); i++)
    {
        for (int j = i + 1; j < s.length(); j++)
        {
            if (j - i + 1 > maxLen && Palindrome(s, i, j))
            {
                maxLen = j - i + 1;
                answer = s.substr(i, j + 1);
            }
        }
    }
    return answer;
}

//Manacher's Algiruthm

//
int main()
{
   // std::cout << GetMinBlocks({ 1,2,5,3,1,0,2,3 }, 6, 3);
    //std::vector<std::vector<int>> fields = {
    //   {0, 1, 0, 2, 1},
    //   {1, 1, 2, 0, 0},
    //   {0, 2, 1, 1, 0},
    //   {1, 0, 0, 1, 2}
    //};
    //int farmSize = 2;

    //// 함수 호출
    //int result = GetMinStones(fields, farmSize);

    //// 결과 출력
    //if (result == -1)
    //{
    //    std::cout << "돌을 제거할 수 없습니다." << std::endl;
    //}
    //else
    //{
    //    std::cout << "최소 돌 제거 개수: " << result << std::endl;
    //}
    //std::vector<int> nums = { 2, 3, 1, 1, 4 };

    //// 함수 호출
    //bool result = CanJump(nums);

    //// 결과 출력
    //if (result)
    //{
    //    std::cout << "끝까지 점프 가능합니다!" << std::endl;
    //}
    //else
    //{
    //    std::cout << "끝까지 점프할 수 없습니다." << std::endl;
    //}

        // 예시 입력: 문자열
    //std::string input = "babad";

    //// 함수 호출
    //std::string result = LongetPalindrome(input);

    //// 결과 출력
    //std::cout << "가장 긴 팰린드롬 부분 문자열: " << result << std::endl;

        // 예시 입력: 문자열과 추가로 바꿀 수 있는 문자 개수
    //std::string input = "ababbc";
    //int k = 2;

    //// 함수 호출
    //int result = LengthOfReplcaementSubstring(input, k);

    //// 결과 출력
    //std::cout << "가장 긴 대체 가능한 부분 문자열의 길이: " << result << std::endl;


    //std::string input = "ababbc";
    //int k = 2;

    //// 함수 호출
    //int result = LengthOfReplcaementSubstring(input, k);

    //// 결과 출력
    //std::cout << "가장 긴 대체 가능한 부분 문자열의 길이: " << result << std::endl;

        // 예시 입력: 정수 배열
    std::vector<int> input = { -2,0,-1 };

    // 함수 호출
    int result = MaxProductOfSubArray2(input);

    // 결과 출력
    std::cout << "부분 배열의 최대 곱: " << result << std::endl;

    return 0;

}


