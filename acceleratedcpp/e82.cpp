// implementing some librayry functions

// equal(b, e, d): if [b, e) equals to [d, ?)
// InIter1 supports: *, ++, ==
// InIter2 supports: *, ++
template<class InIter1, class InIter2>
bool equal(InIter1 b, InIter1, e, InIter2 d)
{
  while (b != e && *b == *d) {
    b++;
    d++;
  }
  return b == e;
}

// search(b, e, b2, e2): look for [b2, e2) in [b, e)
// InIter1 supports: !=, ++ (, * from equal)
// InIter2 supports: (*, ++, == from equal)
template<class InIter1, class InIter2>
InIter1 search(InIter b, InIter e, InIter b2, InIter e2)
{
  while (b != e) {
    if equal(b2, e2, b)
      return b;
    else
      b++;
  }
  return e; // now b == e
}

// find(b, e, t): look for value t in [b, e)
// InIter supports: !=, ++, *
template<class InIter, class V>
InIter find(InIter b, InIter e, V t)
{
  while(b != e && *b != t)
    b++;
  return b;
}

// find_if(b, e, p): look for element when p is true
// InInter supports: !=, *, ++
template<class InIter, class P>
InIter find(InIter b, InIter e, P p)
{
  while (b != e && !p(*b))
    b++;
  return b;
}

// copy(b, e, d)
// InIter supports: !=, *, ++
// OutIter supports: *, ++, =
template<class InIter, class OutIter>
OutIter copy(InIter b, InIter e, OutIter d)
{
  while (b != e)
    *d++ = *b++;
  return d;
}

// remove_copy(b, e, d, t)
// InIter supports: *, !=, ++
// OutIter supports: *, ++, =
template<class InIter, class OutIter, class V)
OutIter remove_copy(InIter b, InIter e, OutIter d, V t)
{
  while (b != e)
    if (*b != t)
      *d++ = *b++;
    else
      b++;
  return d;
}

// remove_copy_if(b, e, d, p)
// InIter supports: !=, *, ++
// OutIter supports: *, ++, =
template<class InIter, class OutIter, class P>
OutIter remove_copy_if(InIter b, InIter e, OutIter d, P p)
{
  while (b != e)
    if p(*b)
      b++
    else
      *d++ = *b++;
  return d;
}

// remove(b, e, t)
// ForIter supports: !=, *, ++, =
template<class ForIter, class V>
InIter remove(ForIter b, ForIter e, V t)
{
  ForIter head = b;
  while (b != e)
    if (*b == t)
      b++
    else
      *head++ = *b++;
  return head;
}

// transform(b, e, d, f)
// InIter supports: !=, *, ++
// OutIter supports: *, ++, =
template<class InIter, class OutIter, class F>
OutIter transform(InIter b, InIter e, OutIter d, F f)
{
  while (b != e)
    *d++ = f(*b++);
  return d;
}

// partition(b, e, p)
// ForIter supports: !=, *, ++, =
template<class ForIter, class P, class V>
ForIter partition(ForIter b, ForIter e, P p)
{
  ForIter head = b;
  V tmp;
  while (b != e)
    if p(*b) { // swap
      tmp = *head;
      *head = *b;
      *b = tmp;
      head++;
    }
    b++;
  return head;
}

// accumulate(b, e, t)
// InIter supports: !=, *, ++
template<class InIter, class V>
V accumulate(InIter b, InIter e, V t)
{
  V ret = t;
  while (b != e)
    ret += *b++;
  return ret;
}
