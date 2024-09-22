
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <string>

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

//6.
int LengthOfReplcaementSubstring(std::string s, int k)
{
    std::unordered_map<char, int> um;
    for (auto c : s)
    {
        um[c]++;
    }
    int max{};
    for (auto e : um)
    {
        max = std::max(max, e.second);
    }

    return max + k;
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
}
