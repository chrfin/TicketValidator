CREATE TABLE cards
(
        card_id int PRIMARY KEY NOT NULL,
        card_code nchar(20) NOT NULL,
        card_name ntext,
        card_address ntext,
        card_zip ntext,
        card_city ntext,
        card_phone ntext,
        card_mail ntext,
        card_redeemed bit DEFAULT 0,
        card_redeem_date datetime
);