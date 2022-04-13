template<typename K, typename V>
class Pair
{
public:
	Pair()
	{

	}

	Pair(const K& key, const V& value)
		: Key(key),
		Value(value)
	{

	}

	Pair(const Pair& rhs)
		: Key(rhs.Key),
		Value(rhs.Value)
	{

	}

	Pair(Pair&& rhs)
	{
		if (&rhs != this)
		{
			Swap(rhs);
		}
	}

	Pair& operator=(const Pair& rhs)
	{
		Key = rhs.Key;
		Value = rhs.Value;
		return *this;
	}

	Pair& operator=(Pair&& rhs)
	{
		if (&rhs != this)
		{
			Swap(rhs);
		}

		return *this;
	}

	bool operator==(const Pair& rhs) const
	{
		return Key == rhs.Key && Value == rhs.Value;
	}

	bool operator!=(const Pair& rhs) const
	{
		return Key != rhs.Key || Value != rhs.Value;
	}

	K Key;
	V Value;
private:
	void Swap(Pair& rhs)
	{
		K key = Key;
		Key = rhs.Key;
		rhs.Key = key;

		V value = Value;
		Value = rhs.Value;
		rhs.Value = value;
	}
};
