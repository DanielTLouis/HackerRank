/*
The Tower of Hanoi is a famous game consisting of 3 rods and a number of discs of
incrementally different diameters. The puzzle starts with the discs neatly stacked on
one rod, ordered by ascending size with the smallest disc at the top. The game's
objective is to move the entire stack to another rod, obeying the following rules:
    1. Only one disk can be moved at a time.
    2. In one move, remove the topmost disk from one rod and move it to another rod.
    3. No disk may be placed on top of a smaller disk.
* https://en.wikipedia.org/wiki/Tower_of_Hanoi *
Gena has a modified version of the Tower of Hanoi. This game of Hanoi has 4 rods and n
disks ordered by ascending size. Gena has already made a few moves following the rules
above. Given the state of Gena's Hanoi, determine the minimum number of moves needed to
restore the tower to its original state with all disks on rod 1.
Note: Gena's rods are numbered from 1 to 4. The radius of a disk is its index in the
input array, so disk 1 is the smallest disk with a radius of 1, and disk n is the
largest with a radius of n.
Example
    posts=[4,3,2,1]
    In this case, the disks are arranged from large to small across the four rods. The
    largest disk, disk 4, is already on rod 1, so move disks 3,2, and 1 to rod 1, in
    that order. It takes 3 moves to reset the game.
    posts=[4,2,2,1]
    The largest disk, disk 4 with radius 4, is already on rod 1. Disk 3 is on rod 2 and
    must be below disk 2. Move disk 2 to rod 3, disk 3 to rod 1 and disk 2 to rod 1. Now
    move disk 1 to rod 1. It takes 3 moves to reset the game.
Function Description
    Complete the hanoi function below.
    hanoi has the following parameters:
        int posts[n]: post[i] is the location of the disk with radius
Returns
    int: the minimum moves to reset the game to its initial state
Input Format
    The first line contains a single integer, n, the number of disks.
    The second line contains n space-separated integers, where the ith integer is the
    index of the rod where the disk with diameter i is located.
Constraints
    1<=n<=10
Sample Input
    STDIN   Function
    -----   --------
    3       size of posts[] n = 3
    1 4 1   posts = [1, 4, 1]
Sample Output
    3
Explanation
    3 moves are enough to build the tower. Here is one possible solution:
        gena1.png
        gena2.png
*/

#include <iostream>
#include <vector>
#include <deque>

unsigned move(const unsigned state, const unsigned rod, const unsigned disc){
  return (state & ~(3<<2*(disc-1))) | rod<<2*(disc-1);
}

unsigned get_disc(const unsigned ndisc, const unsigned state, const unsigned rod){
  unsigned disc=ndisc+1;
  for(unsigned h=ndisc;h!=0;--h){
    unsigned r=3&state>>2*(h-1);
    if(r==rod) disc=h;
  }
  return disc;
}

unsigned long solve(const unsigned ndisc,unsigned start){
  const unsigned win=0;
  if(start==win) return 0;
  std::deque<unsigned> bfs;
  bfs.push_back(start);
  std::vector<unsigned> depth(1<<2*ndisc,0);
  depth[start]=0;
  while(true){
    unsigned par=bfs.front();
    bfs.pop_front();
    unsigned d[4];
    for(unsigned rod=0;rod<4;++rod){
      d[rod]=get_disc(ndisc,par,rod);
    }
    for(unsigned from=0;from<4;++from){
      if(d[from]==ndisc+1) continue;
      for(unsigned to=0;to<4;++to){
    if(d[to]>d[from]){
      unsigned ch=move(par,to,d[from]);
      if(ch==win) return 1+depth[par];
      if(!depth[ch] && ch!=start){
        depth[ch]=1+depth[par];
        bfs.push_back(ch);
      }
    }
      }
    }
  }
  return -1;
}

int main(){
  unsigned ndisc=0, start=0;
  std::cin >> ndisc;
  for(unsigned h=1;h<=ndisc;++h){
    unsigned rod=0;
    std::cin >> rod;
    --rod;
    start=move(start,rod,h);
  }
  std::cout << solve(ndisc,start);
}
