CREATE TABLE IF NOT EXISTS "login_info" (
  "id" integer NOT NULL,
  "name" TEXT NOT NULL,
  "secret_id" TEXT NOT NULL,
  "secret_key" TEXT NOT NULL,
  "remark" TEXT,
  "timestamp" integer NOT NULL,
  PRIMARY KEY ("id"),
  CONSTRAINT "secret_id" UNIQUE ("secret_id" ASC),
  CONSTRAINT "name" UNIQUE ("name" ASC)
);
