 // A module for an int sequence ADT

struct sequence;

// NOTE: All of the following functions REQUIRE:
//       pointers to a sequence (e.g., seq) are valid (not NULL)

// sequence_create() returns a pointer to a new (empty) sequence
// effects: allocates memory (caller must call sequence_destroy)
// time: O(1)
struct sequence *sequence_create(void);

// sequence_destroy(seq) frees all dynamically allocated memory 
// effects: the memory at seq is invalid (freed)
// time: O(n)
void sequence_destroy(struct sequence *seq);

// sequence_length(seq) returns the number of items in seq
// time: O(1)
int sequence_length(const struct sequence *seq);

// sequence_item_at(seq, pos) returns the item in seq at the given pos
// requires: 0 <= pos < length(seq)
// time: O(n)
int sequence_item_at(const struct sequence *seq, int pos);

// sequence_insert_at(seq, pos, val) inserts a new item with value val
//   at position pos in seq
//   (changing the position of items at position >= pos)
// requires: and 0 <= pos <= length(seq)
// effects: seq is modified
// time: O(n)
void sequence_insert_at(struct sequence *seq, int pos, int val);

// sequence_remove_at(seq, pos) removes the item at position pos in seq
//   and returns the removed value
//   (changing the position of items > pos)
// requires: 0 <= pos < length(seq)
// effects: seq is modified
// time: O(n)
int sequence_remove_at(struct sequence *seq, int pos);

// sequence_print(seq) prints out the items in seq
//   using the format: "[item_0,item_1,...,item_last]\n"
//   or "[empty]\n"
// effects: prints out a message
// time : O(n)
void sequence_print(const struct sequence *seq);
