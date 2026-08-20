# CS2040C → Thales interview: what to prioritise

You're on **Week 2 (Analysis of Algorithms)** with ~57 hours to Friday. You cannot
finish a 13-week course by then, and trying would actively hurt you. So this
splits into **what to do before Friday** and **what to do after**.

The good news: Prof Halim's course front-loads almost everything that matters for
an embedded interview, and back-loads almost everything that doesn't.

---

## The two findings that should drive your choices

### 1. Halim's midterm scope *is* the Thales interview scope

The midterm is explicitly **"Material: Up to List… No PQ yet"** — i.e. C++
fundamentals, analysis of algorithms, sorting, and linked lists. Weeks 1–4.

That is almost exactly the surface a Thales embedded round tests. Whereas the
**final** is deliberately graph-heavy — *"at least two of the questions involve
graph (the last four weeks: Week 10-11-12-13)"* — which is the competitive-
programming half and close to irrelevant for Friday.

**So: your self-supervised midterm is the interview-relevant one. Do that one
first, and treat the final as a post-Friday goal.**

### 2. The exam format trains a skill Thales actually tests

Halim's new format hands you up to six GenAI-written answers, of which **at most
one is fully correct (no bug, theoretically fastest)**, and your job is to find
and declare it — with tweaking a correct answer into a wrong one heavily
penalised.

That is **code review under time pressure**. And the reported Thales process
includes *"code review and live coding exercises"* alongside the coding
questions. Practising Halim's format is directly transferable in a way that
grinding more LeetCode arrays is not.

This is worth 45 minutes on Wednesday evening. It is a better use of that slot
than another array problem.

---

## Priority tiers

### 🔴 Tier 1 — before Friday. Everything here appears in an embedded round.

| Wk | Topic | Why it matters on Friday |
|---|---|---|
| **1** | Algorithms on Unsorted Array | Brute force, two-pointer, in-place. This *is* the reported Thales question style ("remove duplicates from an array"). |
| **2** | **Analysis of Algorithms** ← you are here | Where your complexity table comes from. You will be asked "what's the complexity?" after every single answer. Finish this properly — don't rush past it. |
| **3** | **Sorting** | The largest single payload. Stability, in-place, worst cases, and *which sort for a memory-constrained target*. |
| **4** | **List ADT: SLL / Stack / Queue / DLL / Deque** | Reverse a list and cycle detection are the most-asked pointer questions anywhere. **And the circular-array queue is literally the ring buffer** — the classic embedded interview question. |
| **5** | Priority Queue / Binary Heap | Ties straight to heapsort (your best "embedded sort" answer), and a PQ is how you'd build a software timer queue on an MCU. |

### 🟡 Tier 2 — high value, but after Friday unless you're ahead

| Wk | Topic | Interview value |
|---|---|---|
| **8** | Hash Table (chaining vs open addressing, LP/QP/DH) | Genuinely common: "how would you store N keys for fast lookup?" Worth a 20-minute skim Thursday if you have slack — know chaining vs open addressing and the load-factor point. |
| **9** | BST + AVL | Moderate. Know that a BST degenerates to O(n) on sorted input and that AVL exists to fix it. Full rotation mechanics are not Friday material. |

### ⚪ Tier 3 — for course completion, not for Friday

| Wk | Topic | Interview value for *this* role |
|---|---|---|
| 7b | Union-Find Disjoint Sets | Low |
| 10 | Graph DS (adj matrix/list/edge list) | Low |
| 11 | Graph Traversal (DFS/BFS) | Low–moderate (general CS literacy) |
| 12 | SSSP: Bellman-Ford, Dijkstra, DAG DP | Low |
| 13 | MST: Kruskal / Prim | Low |

These are real computer science and worth learning — they're just ICPC-shaped,
and Thales ECC is not hiring for ICPC. **Do not touch them before Friday.**
They're the four weeks the *final* leans on, so they come back when you sit that.

---

## The one warning that matters most

**CS2040C is taught in C++. Thales wants C.**

If your reflex answer to "implement a queue" is `std::queue`, you have failed an
embedded interview. On a secure element there is no STL, often no heap, and
sometimes no `malloc` at all.

So use the course this way:

1. **Concept** → Halim's lecture + VisuAlgo animation
2. **Implementation** → write it in **C**, with fixed-size arrays, explicit
   bounds checks, and every `malloc` checked
3. **Then** learn the C++/STL version, because it's what the course grades

Your `01_sorting.c`, `02_embedded_c.c` and `03_data_structures.c` are exactly
that translation already done — CS2040C content, expressed the way Thales wants
to hear it.

---

## VisuAlgo, filtered

**Before Friday:** `/en/sorting` · `/en/list` · `/en/heap`
**If ahead:** `/en/hashtable` · `/en/bst`
**After Friday:** `/en/ufds` · `/en/graphds` · `/en/dfsbfs` · `/en/sssp` · `/en/mst`

VisuAlgo is excellent for *seeing* an invariant — watch merge sort's merge step
and quicksort's partition until the pointer movement is obvious. But watching is
recognition, not recall. Every animation you watch, close the tab and retype the
algorithm in C.

---

## The plan, sequenced

**Before Friday** (already in your roadmap — Wednesday is a CS2040C day):

- Weeks 1–2 concepts fold into the Wed 08:30 and 13:15 blocks (analysis + the
  complexity table)
- Week 3 is the Wed 09:00–14:30 sorting blocks
- Week 4 is the Wed 16:30 ring buffer + 19:00 linked list blocks
- Week 5 (heap) is inside the Wed 13:15 heapsort block
- **New:** Wed 20:15 code-review drill in Halim's GenAI format

**After Friday**, whatever the outcome:

1. Finish Weeks 5–9 properly (PQ, UFDS, hash, BST/AVL) — ~2 weeks at a sane pace
2. Sit a past **midterm** timed and open-book, 80 minutes. Papers exist for
   AY23/24 S1, AY24/25 S1, AY25/26 S1 and S2.
3. Weeks 10–13 (graphs, SSSP, MST) — ~2–3 weeks
4. Sit a past **final** timed, 2 hours
5. Halim's "Part 0" benchmark: clear 25 of the 33 non-premium LeetCode
   programming-skills problems

---

## What this gives you in the room

You now have a specific, verifiable answer to the transcript question — and
"I'm on Week 2, analysis of algorithms; I did sorting this week and implemented
the full set in C rather than C++ so I could reason about the memory trade-offs
on a constrained target" is a **far** stronger sentence than "I'm brushing up on
data structures."

Specificity is what makes it read as real rather than as something you said
because you were asked.
