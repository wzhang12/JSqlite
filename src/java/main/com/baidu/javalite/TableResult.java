package com.baidu.javalite;

import java.util.Iterator;

/**
 * Created with IntelliJ IDEA.
 * Date: 14-8-25
 */
public class TableResult implements Iterable<TableResult.Cell> {
    private String[] result;
    private int rowNums;
    private int colNums;

    protected TableResult(String[] result, int rowNums, int colNums) {
        if (result == null) {
            this.result = new String[0];
        } else {
            this.result = result;
        }
        this.rowNums = rowNums; // 第一行默认是 headers
        this.colNums = colNums;
    }

    public int getColNums() {
        return colNums;
    }

    public int getRowNums() {
        return rowNums;
    }

    public String getCellData(int row, int col) {
        return result[row * colNums + col];
    }

    public static class Cell {
        public String data;
        public int row;
        public int column;

        @Override
        public String toString() {
            return String.format("[%d, %d]: %s", row, column, data);
        }
    }

    @Override
    public java.util.Iterator<Cell> iterator() {
        return new MyIterator();
    }

    private class MyIterator implements Iterator<Cell> {
        private Cell cell = new Cell();
        private int index = 0;

        @Override
        public boolean hasNext() {
            return index != result.length;
        }

        @Override
        public Cell next() {
            cell.data = result[index];
            cell.row = index / colNums;
            cell.column = index % colNums;
            index++;
            return cell;
        }

        @Override
        public void remove() {
            throw new UnsupportedOperationException();
        }
    }
}
