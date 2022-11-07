# Wizard 2

This is a continuation of the Wizard 1 challenge.

Now the negative value bug is fixed, but now instead you can get the same result by buying enough hats that the signed integer is overflowed.

If you buy 400'000'000 hats, then that will cost 4'000'000'000 which when wrongfully being converted into a signed integer resulting in a negative number.