/* syntax version 1 */
/* skip double format */
use plato;
PRAGMA AnsiInForEmptyOrNullableItemsCollections;

$src = (select cast(key as Int32) from Input);

select ListFilter(ListFromRange(1, 100), ($i) -> { RETURN $i IN $src; });
