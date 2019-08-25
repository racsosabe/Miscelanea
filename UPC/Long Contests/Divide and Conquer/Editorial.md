Hola a todos, acá dejo los tutoriales de cada problema (algunos son los mismos que tuvieron en su contest original y otros son un enfoque usando D&C si es posible). Algunos problemas son de temas diferentes a D&C y otros con temas avanzados, pero recuerden que siempre tienen que esperar lo que sea en un contest :D

[A. Imbalanced Array](https://codeforces.com/group/Hz7jTE3LqO/contest/249674/problem/A)
------------------

To solve this problem we can handle the sum:

$$ S = \sum\limits_{l \leq r}max(a_{l},\ldots,a_{r}) - min(a_{l},\ldots,a_{r}) $$

And separate the terms:

$$ S = \sum\limits_{l \leq r}max(a_{l},\ldots,a_{r}) - \sum\limits_{l \leq r}min(a_{l},\ldots,a_{r}) $$

Thus, we can get both sums independently and using divide and conquer with a Mergesort style.

[B. Pashmak and Parmida's problem](https://codeforces.com/group/Hz7jTE3LqO/contest/249674/problem/B)
------------------

We can preprocess two arrays $prefix$ and $suffix$ such that $prefix_{i} = f(1,i,a_{i})$ and $suffix_{i} = f(i,n,a_{i})$ and the problem reduces to find the crossed inversions in between the two arrays (All $i < j$ such that $prefix_{i} > suffix_{j}$).

We can solve this problem using divide and conquer with a Mergesort style.

[C. Equivalent Strings](https://codeforces.com/group/Hz7jTE3LqO/contest/249674/problem/C)
------------------

Let us note that "equivalence" described in the statements is actually equivalence relation, it is reflexively, simmetrically and transitive. It is meant that set of all string is splits to equivalence classes. Let's find lexicographic minimal strings what is equivalent to first and to second given string. And then check if its are equals.

It is remain find the lexicographic minimal strings what is equivalent to given. For instance we can do it such a way:

~~~~~
String smallest(String s) {
    if (s.length() % 2 == 1) return s;
    String s1 = smallest(s.substring(0, s.length()/2));
    String s2 = smallest(s.substring(s.length()/2), s.length());
    if (s1 < s2) return s1 + s2;
    else return s2 + s1;
}
~~~~~

Every recursive call time works is $O(n)$ (where n is length of strings) and string splitten by two twice smaller strings. Therefore time of work this function is $O(nlogn)$, where $n$ is length of strings.

[D. The Brand New Function](https://codeforces.com/group/Hz7jTE3LqO/contest/249674/problem/D)
------------------

Let's see how function $f$ changes for all suffixes of sequence $a$. Values of $f$ will increase when you will increase length of suffix. For every increase all 1-bits will stay 1-bits, but some 0-bits will be changed by 1-bits. So, you can see that no more than $k$ increasing will be, where $k$ number of bits (in this problem $k = 20$). Among all suffixes will be no more that $k + 1$ values of function $f$.

Now you can run over sequence $a$ from left to right and support an array $m$ (or a set) of values of $f$ for all subsegments that end in the current position. Size of $m$ always no more than $k + 1$. When you go from position $i - 1$ into position $i$, you should replace $m = (m1, m2, ..., mt)$ by $m' = (ai, m1|ai, m2|ai, ... mt|ai)$. After that you should remove from $m$ repeated values (if you use set, set will do this dirty work itself). Then you should mark all numbers from $m$ in some global array (or put them into some global set). At the end you should calculate answer from the global array (or set).

[E. Package Delivery](https://codeforces.com/group/Hz7jTE3LqO/contest/249674/problem/E)
------------------

We solve this with a greedy algorithm: for each gas station, we fill our tank to $min(n, d)$ liters of gasoline, where $d$ is the distance to the next gas station with cheaper (or equal) gas. This is optimal, as, if we can make it to a station with cheaper gas without buying expensive gas, we should (and fill up our tank at the cheaper station). Otherwise, all stations within range n are more expensive, so we should buy as much gas as possible right now.

Alternatively, if we say that we always “use” the gasoline we buy in the order we buy it, then the gasoline used in the ith unit must have been purchased within the last $n$ units. Then we can greedily use the cheapest gas within the last $n$ miles. We can maintain this in a queue with range-min-query, which gives us linear runtime (after sorting).

[F. Maximum Median](https://codeforces.com/group/Hz7jTE3LqO/contest/249674/problem/F)
------------------

Sort the array in non-decreasing order. In the new array 𝑏1,𝑏2,…,𝑏𝑛 you can make binary search with the maximum median value. For a given median value (𝑥), it is required to make $\sum 𝑛𝑖=(𝑛+1)/2𝑚𝑎𝑥(0,𝑥−𝑏𝑖)$ operations. If this value is more than 𝑘, 𝑥 can't be median, otherwise it can. Time complexity: $O((\frac{n}{2})⋅𝑙𝑜𝑔(109))$


