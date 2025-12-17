class HashTable:
    def __init__(self, size=10):
        """
        Initialize the hash table with a fixed size.
        Each bucket is an empty list to handle collisions (Chaining).
        """
        self.size = size
        self.table = [[] for _ in range(self.size)]
        self.count = 0  # To track load factor if needed

    def _hash(self, key):
        """
        A simple hash function.
        Uses the built-in hash() and modulo arithmetic.
        """
        return hash(key) % self.size

    def insert(self, key, value):
        """
        Inserts a key-value pair.
        If key exists, update the value.
        If collision occurs, append to the chain.
        """
        index = self._hash(key)
        bucket = self.table[index]

        # Check if key already exists (Update)
        for i, (k, v) in enumerate(bucket):
            if k == key:
                bucket[i] = (key, value)  # Update value
                return

        # If key not found, append new pair (Collision handling)
        bucket.append((key, value))
        self.count += 1

    def search(self, key):
        """
        Looks for the key in the calculated bucket.
        Returns value if found, else None.
        """
        index = self._hash(key)
        bucket = self.table[index]

        for k, v in bucket:
            if k == key:
                return v  # Found

        return None  # Not found

    def delete(self, key):
        """
        Removes a key-value pair if it exists.
        """
        index = self._hash(key)
        bucket = self.table[index]

        for i, (k, v) in enumerate(bucket):
            if k == key:
                del bucket[i]  # Remove from chain
                self.count -= 1
                return True

        return False  # Key not found

    def __str__(self):
        """
        Helper to visualize the table
        """
        output = []
        for i, bucket in enumerate(self.table):
            output.append(f"Bucket {i}: {bucket}")
        return "\n".join(output)


# --- Testing the Implementation ---
ht = HashTable(size=5)

print("--- Inserting Data ---")
ht.insert("apple", 10)
ht.insert("banana", 20)
ht.insert("grape", 30)
ht.insert("apple", 15)  # Update "apple"
ht.insert("orange", 50)  # Likely a collision in small table

print(ht)

print("\n--- Searching ---")
print(f"Price of apple: {ht.search('apple')}")  # Should be 15
print(f"Price of mango: {ht.search('mango')}")  # Should be None

print("\n--- Deleting ---")
ht.delete("banana")
print(ht)
