
本 Vault 收錄你所有資料結構／演算法模板（C 語言實作）對應的設計說明／備註。  
實際 code 實現在 `src/` 下；說明文件在本 vault。  

---

## Quick guides

- [Getting Started]([[Getting Started]])  ← 若你想加 general usage、說明如何 compile/run  
- [How to use this vault]([[How to use this vault]])  ← vault／GitHub + workflow 說明  

---

## Data Structure Categories

### 🧰 Stack & Queue  
- [[Stack]]  
- [[Queue (Array)]]  
- [[Queue (Linked List)]]  
- [[Priority Queue]]  

### 🔢 Hash Table  
- [[Hash — Separate Chaining (Linked List)]]  
- [[Hash — Linear Probing]]  
- [[Hash — Quadratic Probing]]  
- [[Hash — Double Hashing]]  

### 🌳 Tree & Heap  
- [[Binary Search Tree (BST)]]  
- [[Max Heap]]  
- [[Leftist / NPL Tree]]  
- [[Min-Max Heap / Deap / SMMH]]  
- [[AVL Tree]]  

### 🔗 Graph & Graph Algorithms  

#### Traversal / Basic  
- [[Graph — BFS / DFS]]  
- [[Graph — Topological Sort]]  
- [[Graph — Connected Components (DSU)]]  
- [[Graph — Bipartite Check]]  

#### Shortest Path / Pathfinding  
- [[Graph — BFS (unweighted pathfinding)]]  
- [[Graph — Dijkstra]]  
- [[Graph — Bellman–Ford]]  

#### MST (Minimum Spanning Tree)  
- [[Graph — Kruskal (MST)]]  
- [[Graph — Prim (MST)]]  

#### Graph Data Structures / Utilities  
- [[Graph — Union-Find (DSU)]]  

---

## Others / Utilities  
（如果未來有 String / Geometry / Flow / Segment Tree / … 類別可以加在這裡）  

---

## About / References  
- [README (GitHub)](../README.md) — code repo 入口 & compile instruction  
- [License & Code conventions]([[Code Conventions]]) — 如果你想定規 code style / commit 規則  

---

> **Tips**  
> - 每個 `[[XXX]]` 對應一個 .md 檔案（例如 `AVL Tree.md`）  
> - 在各檔案裡，記錄資料結構特性／invariant／interface／用法／邊界條件／範例 code path。  
> - 保持 code ↔ doc 的對應關係：不在 doc 重複 code，而是寫 mental model / 注意事項。  
> - 如你日後 template 增多，可依這個 index 更新分類。  