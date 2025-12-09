#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_SIZE 100

typedef struct {
    int A[MAX_SIZE + 1]; // 陣列，索引 1 為 Root (Empty)，數據從 2 開始
    int n;               // 堆中元素的數量
} SMMH;

int is_valid(SMMH* heap, int i) {
    return (i >= 2 && i <= heap->n);
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int Parent(int i) { return i / 2; }
int LeftChild(int i) { return 2 * i; }
int RightChild(int i) { return 2 * i + 1; }

int Sibling(int i) {
    if (i == 2) return 3;
    if (i == 3) return 2;
    return (i % 2 == 0) ? i + 1 : i - 1;
}

// ---------- Main Operations ----------

void initialize_smmh(SMMH* heap) {
    heap->n = 0;
    heap->A[1] = INT_MIN; 
}

int FindMin(SMMH* heap) { // O(1)
    if (heap->n < 1) return INT_MIN;
    return heap->A[2];
}

int FindMax(SMMH* heap) {
    if (heap->n == 0) return INT_MIN;
    if (heap->n == 1) return heap->A[2];
    return heap->A[3];
}

// For Insert
void bubble_up(SMMH* heap, int i) {
    if (i <= 3) return;

    int P = Parent(i);
    int G_L = 2 * (P / 2); // grandparent's leftchild
    int G_R = G_L + 1;     // grandparent's rightchild

    while (i >= 4) {
        P = Parent(i);
        G_L = 2 * (P / 2);
        G_R = G_L + 1;

        if (i == LeftChild(P)) {
            if (heap->A[i] < heap->A[G_L]) {
                swap(&heap->A[i], &heap->A[G_L]);
                i = G_L;
            } else {
                break;
            }
        }
        
        else {
            if (heap->A[i] > heap->A[G_R]) {
                swap(&heap->A[i], &heap->A[G_R]);
                i = G_R;
            } else {
                break;
            }
        }

        i = Parent(Parent(i)); // 向上跳兩層
    }
}

void Insert(SMMH* heap, int x) {
    if (heap->n >= MAX_SIZE) {
        printf("Error: Heap is full.\n");
        return;
    }

    heap->n++;
    int i = heap->n + 1;
    heap->A[i] = x;

    if (heap->n == 1) return; // 只有一個元素，已放在 A[2]

    if (i == 3) {
        if (heap->A[2] > heap->A[3]) {
            swap(&heap->A[2], &heap->A[3]);
        }
        return;
    }

    int S = Sibling(i);
    
    if (i % 2 == 0 && is_valid(heap, S) && heap->A[i] > heap->A[S]) {
        swap(&heap->A[i], &heap->A[S]);
        i = S; // 交換後，在右子位置進行 Grandparent 調整
    } 
    // 如果 i 是右子 (Max Path)
    else if (i % 2 != 0 && is_valid(heap, S) && heap->A[i] < heap->A[S]) {
        swap(&heap->A[i], &heap->A[S]);
        i = S; // 交換後，在左子位置進行 Grandparent 調整
    }

    // 3. 祖父節點調整 (Grandparent Adjustment)
    bubble_up(heap, i);
}


// 找到子樹中最極端的元素索引 (DeleteMin 找 Min, DeleteMax 找 Max)
int find_extreme_index(SMMH* heap, int i, int is_min) {
    int extreme_idx = i;
    int extreme_val = is_min ? INT_MAX : INT_MIN;

    // 查找範圍：i 的子節點 (L, R) 和孫子節點 (4 個)

    // 1. 檢查子節點
    int L = LeftChild(i);
    int R = RightChild(i);

    if (is_valid(heap, L)) {
        if (is_min) {
            if (heap->A[L] < extreme_val) { extreme_val = heap->A[L]; extreme_idx = L; }
        } else {
            if (heap->A[L] > extreme_val) { extreme_val = heap->A[L]; extreme_idx = L; }
        }
    }
    // 注意：對於 Min Path i，只需檢查其 Min Child；對於 Max Path i，只需檢查其 Max Child
    // 這裡為了簡化，檢查所有子節點和孫節點

    // 2. 檢查孫子節點 (LeftChild(L), RightChild(L), LeftChild(R), RightChild(R))
    for (int k = 0; k < 4; k++) {
        int G = 2 * L + k; // 孫子索引 (從 LeftChild(L) 開始)
        if (is_valid(heap, G)) {
            if (is_min) {
                if (heap->A[G] < extreme_val) { extreme_val = heap->A[G]; extreme_idx = G; }
            } else {
                if (heap->A[G] > extreme_val) { extreme_val = heap->A[G]; extreme_idx = G; }
            }
        }
    }
    
    return extreme_idx;
}


// 下沉主邏輯
void sift_down(SMMH* heap, int i, int is_min) {
    while (LeftChild(i) <= heap->n) { // 只要 i 不是葉子節點
        
        // 1. 查找子樹中最極端的元素 k (Min for DeleteMin, Max for DeleteMax)
        int k_idx = find_extreme_index(heap, i, is_min);

        // 如果 k 是 i 自己或不存在，表示已到定位，但 SMMH 需考慮孫子
        if (k_idx == i) {
            // 這裏需要更精確的 SMMH 比較邏輯：檢查 x 和 L/R/孫子中的極值
            // 由於 FindExtremeIndex 已經包含了 L/R 和孫子，我們只需要檢查 A[i] 是否已到位
            if ((is_min && heap->A[i] <= heap->A[k_idx]) || (!is_min && heap->A[i] >= heap->A[k_idx])) {
                 break;
            }
        }

        // 2. 進行交換
        if ((is_min && heap->A[i] > heap->A[k_idx]) || (!is_min && heap->A[i] < heap->A[k_idx])) {
            swap(&heap->A[i], &heap->A[k_idx]);
            
            // 3. 檢查並修復兄弟約束
            int P_k = Parent(k_idx);
            int S_k = Sibling(k_idx);
            
            if (P_k == Parent(i) && S_k == Sibling(i)) {
                // 如果交換發生在子節點 (k_idx is L or R)
                // 兄弟約束已經在 Insert 時處理，Delete 時只需關注孫子調整
            } else if (Parent(P_k) == i) {
                // 如果交換發生在孫子節點 (k_idx is a Grandchild)
                // 確保 P_k 的 Left Child <= Right Child
                if (P_k % 2 == 0 && is_valid(heap, S_k) && heap->A[P_k] > heap->A[S_k]) {
                    swap(&heap->A[P_k], &heap->A[S_k]);
                }
                if (P_k % 2 != 0 && is_valid(heap, S_k) && heap->A[P_k] < heap->A[S_k]) {
                    swap(&heap->A[P_k], &heap->A[S_k]);
                }
            }
            
            i = k_idx; // 繼續向下調整
        } else {
            break;
        }
    }
}

int DeleteMin(SMMH* heap) {
    if (heap->n == 0) {
        printf("Error: Heap is empty.\n");
        return INT_MIN;
    }

    int min_val = heap->A[2]; 
    
    // 1. 取出最小值，用最後一個元素替換 A[2]
    heap->A[2] = heap->A[heap->n + 1]; 
    heap->n--;

    // 2. SiftDownMin：將新元素從 A[2] 向下調整
    sift_down(heap, 2, 1); // 1 for Min

    return min_val;
}

// 7. 刪除最大值 (DeleteMax) (O(log n))
int DeleteMax(SMMH* heap) {
    if (heap->n == 0) {
        printf("Error: Heap is empty.\n");
        return INT_MIN;
    }

    int max_val = heap->A[3]; 
    
    // 1. 取出最大值，用最後一個元素替換 A[3]
    heap->A[3] = heap->A[heap->n + 1];
    heap->n--;

    // 2. SiftDownMax：將新元素從 A[3] 向下調整
    sift_down(heap, 3, 0); // 0 for Max

    return max_val;
}

// ---------- Main Test Program ----------

void print_heap(SMMH* heap) {
    printf("Current SMMH (Size: %d): [", heap->n);
    for (int i = 2; i <= heap->n + 1; i++) {
        printf("%d", heap->A[i]);
        if (i < heap->n + 1) printf(", ");
    }
    printf("]\n");
}

int main() {
    SMMH my_heap;
    initialize_smmh(&my_heap);

    printf("--- SMMH Operations Test ---\n");

    // 插入測試
    Insert(&my_heap, 50);
    Insert(&my_heap, 20);
    Insert(&my_heap, 80);
    Insert(&my_heap, 10);
    Insert(&my_heap, 90);
    Insert(&my_heap, 30);
    Insert(&my_heap, 70);
    
    printf("\nAfter Insertion:\n");
    print_heap(&my_heap);

    printf("\nFindMin: %d\n", FindMin(&my_heap));
    printf("FindMax: %d\n", FindMax(&my_heap));

    int min_removed = DeleteMin(&my_heap);
    printf("\nDeleted Min: %d\n", min_removed);
    printf("After DeleteMin:\n");
    print_heap(&my_heap);

    int max_removed = DeleteMax(&my_heap);
    printf("\nDeleted Max: %d\n", max_removed);
    printf("After DeleteMax:\n");
    print_heap(&my_heap);

    min_removed = DeleteMin(&my_heap);
    printf("\nDeleted Min: %d\n", min_removed);
    printf("After DeleteMin (2nd):\n");
    print_heap(&my_heap);
    
    return 0;
}