/* skip double format */
SELECT
    AsList(
        ListMap(AsList(1,2),($x)->{
            return $x+Yql::Fold(AsList(1),0,($a,$b)->{return $a+$b})
        }),
        ListMap(AsList(1,2),($x)->{
            return $x+Yql::Fold(AsList(1),0,($a,$b)->{return $a+$b})
        })
    );
